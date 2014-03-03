#include "players.hpp"
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

Joueur::Joueur()
{
  T=NULL;
  P=NULL;
  Pnext=NULL;
  score=0;
}
void Joueur::init(int w,int h)
{
  T=new Grille(w,h);
  newTetromino();
}
Joueur::~Joueur()
{
  delete T;
  delete P;
  delete Pnext;
}

void Joueur::newTetromino()
{
  assert(T!=NULL);
  if (P!=NULL) delete P;
  if (Pnext != NULL) 
    {
      P=Pnext;
    }
  else
    {
      int r=rand()%NBTETRO;
      P = new Tetrominos(r,T->sx/2-2,T->sy-4);
    }
  int r=rand()%NBTETRO;
  Pnext = new Tetrominos(r,T->sx/2-2,T->sy-4);
}



void Joueur::getKey(int key)
{
  switch (key) {
  case GLUT_KEY_RIGHT:
    move(+1,0);
    break;
  case GLUT_KEY_LEFT: 
    move(-1,0);
    break;
  case GLUT_KEY_UP:  
    turn(1);
    break;
  case GLUT_KEY_DOWN: 
    fall();
    break;
  }
}


void Joueur::update(int& nbl)
{
  nbl=0;
  if (!move(0,-1))
    {
      fapply(nbl);
      newTetromino();
    }
}


bool Joueur::move(int x,int y)
{
  P->move(x,y);
  if (!fisValid()) 
    {
      P->move(-x,-y);
      return false;
    }
  return true;
}
bool Joueur::turn(int s)
{
  P->turn(s);
  if (!fisValid()) 
    {
      P->turn(-s);
      return false;
    }
  return true;
}
void Joueur::fall()
{
  while (move(0,-1)) {}
}


void IA::newTetromino()
{
  Joueur::newTetromino();
  instructions(T,P->type,Pnext->type,xobj,robj);
}

void IA::moveIA()
{
  if (P->rot != robj) 
    turn(+1);
  else if (P->pos[0] < xobj)
    move(+1,0);
  else if (P->pos[0] > xobj)
    move(-1,0);
  else if (level>5)
    fall();
}


Tetris::Tetris(int w,int h,int n,int lv)
{
  sx=w;
  sy=h;
  level=lv;
  nbj=n;
  nbh=std::min(1,n);
  nbIA=nbj-nbh;
  vJ.resize(nbj,NULL);
  for(int j=0;j<nbh;j++)
    {
      vJ[j]= new Joueur;
      vJ[j]->init(w,h);
    }
  for(int j=nbh;j<nbh+nbIA;j++)
    {
      vJ[j]= new IA;
      vJ[j]->init(w,h);
      vJ[j]->level=level;
    }
}
Tetris::~Tetris()
{
  for(int j=0;j<nbh+nbIA;j++)
    {
      delete vJ[j];
    }
}
void Tetris::update()
{
  int nbl;
  bool disp_scores=false;
  for(int j=0;j<nbj;j++)
    {
      vJ[j]->update(nbl);
      assert(nbl<5);
      if (nbl>0)
	{
	  vJ[j]->score+=SCORE[nbl];
	  disp_scores=true;
	}
    }
  if (disp_scores)
    {
      std::cout<<"scores :";
      for(int j=0;j<nbj;j++)
	std::cout<<vJ[j]->score<<" ";
      std::cout<<std::endl;
    }
}
void Tetris::IAupdate()
{
  for(int j=nbh;j<nbh+nbIA;j++)
    {
      vJ[j]->moveIA();
    }
}



// ------------- //
//   Affichage
// ------------- //

std::vector<float> Tetris::winBounds()
{
  std::vector<float> v(4,0.0);
  v[1]=(float)(sx*nbj);
  v[3]=(float)sy;
  return v;
}

void Tetris::gldisplay()
{
  glPushMatrix();
  for(int j=0;j<nbj;j++)
    {
      if (j>0) glTranslatef((float)sx,0.0f,0.0f);
      vJ[j]->P->gldisplay();
      vJ[j]->T->gldisplay();
    }
  glPopMatrix();
}



// ----------------------
//        IA
// ----------------------


float simulation(const GrilleIA& Gref, int type)
{
  float m=INF;
  int nbl;
  bool modif=false;
  GrilleIA G(Gref);
  Tetrominos P(type); 

  for(int s2=0;s2<4;s2++)
    for(int x2=0;x2<Gref.sx+1;x2++)
      {
	if (modif) G=Gref;

	// on place la piece
	setPositionIA(&P,&G,x2,s2);

	modif=apply(&P,&G,nbl);
	if (!modif) continue; // ça bloque

	m=std::min(m,G.score());	
      }
  return m;
}

float instructions(const Grille* pT,int type1,int type2,int& xmin, int& rmin)
{
  GrilleIA Gref(pT);
  GrilleIA G(Gref);
  Tetrominos P(type1);

  float min,m;
  min=INF;
  int nbl=0;
  bool modif=false;

  for(int s1=0;s1<4;s1++)
    for(int x1=0;x1<Gref.sx+1;x1++)
      {
	if (modif) G=Gref;

	// on place la piece
	setPositionIA(&P,&G,x1,s1);

	// on l'ajoute à la grille
	modif = apply(&P,&G,nbl);
	if (!modif) continue; // ça bloque
	m=simulation(G,type2);
	if (m<min) 
	  {
	    min=m;
	    xmin=x1;
	    rmin=s1;
	  }
      }
  return min;
}

