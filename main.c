#include<stdio.h>
#include<stdlib.h>
#include<raylib.h>
#include<stdbool.h>
#include<time.h>







typedef enum
{
   NORTE      =  0,
   NOROESTE   =  1,
   NORESTE    =  2,
   SUR   	  =  3,
   SUROESTE	  =  4,
   SURESTE    =  5,
   ESTE  	  =  6,
   ESTESUR    =  7,
   ESTENORTE  =  8,
   OESTE      =  9,
   OESTENORTE = 10,
   OESTESUR   = 11

}DIRECCION;








typedef struct serpiente
{
  int            	 pos_memo;
  float             	x_pos;
  float             	y_pos;
  float				  	   wh;
  DIRECCION             	a;
  struct serpiente *siguiente;
}*SERPIENTE;








const int ScreenWidth  =640;
const int ScreenHeight =480;






void       GameLoop();
bool 	   HitRecompensa(Rectangle recompensa,SERPIENTE a);
Rectangle  NuevaRecompensa(Rectangle recompensa,SERPIENTE a,bool *grow);
SERPIENTE  NuevaSerpiente(SERPIENTE original);
SERPIENTE  movimiento(SERPIENTE original);
SERPIENTE EliminarSerpienteMov(SERPIENTE original);
SERPIENTE NuevaSerpienteMov(SERPIENTE original,DIRECCION dir);
SERPIENTE crearmovimiento(SERPIENTE original,SERPIENTE aux,DIRECCION dir);
DIRECCION GetDir(SERPIENTE original,SERPIENTE aux);







int main(void)
{

  InitWindow(ScreenWidth,ScreenHeight,"Snake");

  SetTargetFPS(60);

  GameLoop();


return 0;
}







void GameLoop()
{

   SERPIENTE 	 serpiente;
   SERPIENTE         copia;
   Rectangle 	recompensa;
   bool          isgrowing;

   serpiente=(SERPIENTE)malloc(sizeof(struct serpiente));

   serpiente->a		   = 	   	   OESTE;
   serpiente->pos_memo =	       	   0;
   serpiente->x_pos	   =	rand()%629+1;
   serpiente->y_pos	   =	rand()%469+1;
   serpiente->wh	   =		      10;
   serpiente->siguiente=			NULL;



   srand(time(NULL));
   recompensa.height=	10.0f;
   recompensa.width	=	10.0f;


   recompensa.x	=	rand()%629+1;
   recompensa.y	=	rand()%469+1;






	while(!WindowShouldClose())
	{
		isgrowing=false;
	    recompensa=NuevaRecompensa(recompensa,serpiente,&isgrowing);

	    if( isgrowing == true)serpiente=NuevaSerpiente(serpiente);


	   	serpiente=movimiento(serpiente);


	    copia=serpiente;



		BeginDrawing();
		ClearBackground(RAYWHITE);

	    while(!(copia == NULL))
	    {


	        Rectangle cuadro;

	        cuadro.x		= copia->x_pos;
			cuadro.y		= copia->y_pos;
			cuadro.height	= 	     10.0f;
			cuadro.width 	= 	     10.0f;


	    	DrawRectangleRec(cuadro,BLUE);
	    	DrawRectangleRec(recompensa,RED);

	      copia=copia->siguiente;

	    }



		EndDrawing();
	}

}













Rectangle NuevaRecompensa(Rectangle recompensa,SERPIENTE a, bool *grow)
{
	if(HitRecompensa(recompensa,a))
	{
	   *grow=true;
	   srand(time(NULL));

	   recompensa.x = rand()%629+1;
       recompensa.y = rand()%469+1;

       return recompensa;
	}
	else
	   return recompensa;

}











bool HitRecompensa(Rectangle recompensa,SERPIENTE a)
{

	Rectangle aux;
	aux.height=10.0f;
	aux.width=10.0f;
	aux.x=a->x_pos;
	aux.y=a->y_pos;


	return CheckCollisionRecs(recompensa,aux);

}















SERPIENTE NuevaSerpiente(SERPIENTE original)
{
	if(original->siguiente==NULL)
	{
	  SERPIENTE nueva=(SERPIENTE)malloc(sizeof(struct serpiente));

	  switch(original->a)
	  {
	   case NORTE:{

		   nueva->x_pos=original->x_pos;
		   nueva->y_pos=original->y_pos+1.0f;

		   nueva    -> a        = NORTE;

		   break;
	   }

	   case NORESTE:{

		   nueva->x_pos=original->x_pos;
		   nueva->y_pos=original->y_pos+1.0f;

		   original -> a	    = ESTE;
		   nueva    -> a		= ESTE;

		   break;
	   }

	   case NOROESTE:{

		   nueva->x_pos=original->x_pos;
		   nueva->y_pos=original->y_pos+1.0f;

		   original -> a         = OESTE;
		   nueva	-> a	     = OESTE;

		   break;
	   }

	   case SUR:{

		   nueva->x_pos=original->x_pos;
		   nueva->y_pos=original->y_pos-1.0f;

		   break;
	   }

	   case SUROESTE:{

		   nueva->x_pos=original->x_pos;
		   nueva->y_pos=original->y_pos-1.0f;

		   original -> a         = OESTE;
		   nueva	-> a	     = OESTE;

		   break;
	   }

	   case SURESTE:{

		  nueva->x_pos=original->x_pos;
		  nueva->y_pos=original->y_pos-1.0f;

		  original -> a	    = ESTE;
		  nueva    -> a		= ESTE;

		   break;
	   }

	   case ESTE:
	   {

		  nueva->x_pos=original->x_pos+1.0f;
		  nueva->y_pos=original->y_pos;

		  nueva    -> a		= ESTE;

		   break;
	   }

	   case ESTENORTE:
	   {

		  nueva->x_pos=original->x_pos+1.0f;
		  nueva->y_pos=original->y_pos;

		  original ->a		= NORTE;
		  nueva	   ->a		= NORTE;

		   break;
	   }

	   case ESTESUR:
	   {

		  nueva->x_pos=original->x_pos+1.0f;
		  nueva->y_pos=original->y_pos;

		  original ->a		= SUR;
		  nueva	   ->a		= SUR;

		   break;
	   }

	   case OESTE:
	   {

		  nueva->x_pos=original->x_pos+1.0f;
		  nueva->y_pos=original->y_pos;

		  nueva	   ->a		= OESTE;

		   break;
	   }

	   case OESTENORTE:
	   {

		  nueva->x_pos=original->x_pos-1.0f;
		  nueva->y_pos=original->y_pos;

		  original ->a		= NORTE;
		  nueva	   ->a		= NORTE;

		   break;
	   }

	   case OESTESUR:
	   {

		  nueva->x_pos=original->x_pos-1.0f;
		  nueva->y_pos=original->y_pos;

		  original ->a		= SUR;
		  nueva	   ->a		= SUR;

		   break;
	   }

	  }

	  	  nueva->pos_memo=original->pos_memo+1;
	  	  nueva->wh=10;
	  	  nueva->siguiente=NULL;

	  	  original->siguiente=nueva;

	  	 return original;
	}
	else
	    original->siguiente=NuevaSerpiente(original->siguiente);



 return original;
}







SERPIENTE  movimiento(SERPIENTE original)
{



		if(IsKeyDown(KEY_UP))
		{

		 original=	 NuevaSerpienteMov( original,NORTE);
		 original=      EliminarSerpienteMov( original);


		}


	   	if(IsKeyDown(KEY_DOWN))
	   	{

	   		original=	 NuevaSerpienteMov( original,SUR);
	   	    original=     EliminarSerpienteMov( original);




	   	}


	   	if(IsKeyDown(KEY_RIGHT))
	   	{

	   		original=	   NuevaSerpienteMov(original,ESTE);
	   		original=        EliminarSerpienteMov(original);

	   	}








	   if(IsKeyDown(KEY_LEFT)){

		   original=   NuevaSerpienteMov( original,OESTE);
		   original=      EliminarSerpienteMov( original);

	   }
	   	else
	   	{
	   		original= NuevaSerpienteMov(original,original->a);
	   		original=          EliminarSerpienteMov(original);
	   	}




	return original;
}




SERPIENTE crearmovimiento(SERPIENTE original,SERPIENTE aux,DIRECCION dir)
{



	switch(dir)
	{
		case NORTE:
		{
		  if(original->a != SUR)
		  {
			  if(original->a != NORTE)
			  {

				  aux->a		=	              NORTE;
				  aux->wh		=					 10;
				  aux->x_pos	=	    original->x_pos;
				  aux->y_pos	= original->y_pos-1.0f;
				  aux->pos_memo	=					  0;
				  original->a   =  GetDir(original,aux);
				  aux->siguiente=			   original;

			  }
			  else
			  {

				  aux->a	    =	              NORTE;
				  aux->wh		=					 10;
				  aux->x_pos    =	    original->x_pos;
				  aux->y_pos    = original->y_pos-1.0f;
				  aux->pos_memo = 					  0;
				  aux->siguiente=			   original;

			  }
		  }
		   else
		   	   {
			       aux->a	    = 		   		     SUR;
			       aux->wh	    =					  10;
			       aux->x_pos   =	     original->x_pos;
				   aux->y_pos   =  original->y_pos+1.0f;
				   aux->pos_memo=					   0;
				   aux->siguiente=			    original;
		   	   }

			break;
		}
		case ESTE:
		{
			if(original->a != OESTE)
			{
				if(original->a != ESTE)
				{

					aux->a		  =	                    ESTE;
					aux->wh		  =		    		      10;
					aux->x_pos	  =	   original->x_pos+1.0f;
					aux->y_pos	  =	         original->y_pos;
					aux->pos_memo =		        	       0;
					original->a   =     GetDir(original,aux);
					aux->siguiente=			        original;

				}
				else
				 {

				   aux->a	     =	                  ESTE;
				   aux->wh		 =					    10;
				   aux->x_pos    =	 original->x_pos+1.0f;
				   aux->y_pos    =	       original->y_pos;
				   aux->pos_memo =					     0;
				   aux->siguiente=			      original;

				  }
				}
				 else
				  {
				    aux->a	      = 		   		 OESTE;
					aux->wh	      =					    10;
				    aux->x_pos    =	 original->x_pos-1.0f;
				    aux->y_pos    =		   original->y_pos;
					aux->pos_memo =					     0;
					aux->siguiente=			      original;
			      }

						break;


		}

		case OESTE:
		{
			if(original->a != ESTE)
			{
				if(original->a != OESTE )
				{

						aux->a		=	               OESTE;
						aux->wh		=			   		  10;
						aux->x_pos	=  original->x_pos-1.0f;
						aux->y_pos	=	     original->y_pos;
						aux->pos_memo =				       0;
						original->a   = GetDir(original,aux);
						aux->siguiente=			    original;

				}
				 else
					{

					   aux->a	     =	                OESTE;
					   aux->wh		 =    				   10;
					   aux->x_pos    =  original->x_pos-1.0f;
					   aux->y_pos    =	      original->y_pos;
					   aux->pos_memo =			    		0;
					   aux->siguiente=			     original;

					}
			}
			 else
				{

				   aux->a	  = 		   		      ESTE;
				   aux->wh	  =					        10;
				   aux->x_pos =		 original->x_pos+1.0f;
				   aux->y_pos =		       original->y_pos;
				   aux->pos_memo=					     0;
				   aux->siguiente=			      original;

				}

			break;


		}


		case SUR:
		{
			if(original->a != NORTE)
			{
			  if(original->a != SUR)
			  {

				aux->a		  =	                   SUR;
				aux->wh		  =					    10;
				aux->x_pos	  =	       original->x_pos;
				aux->y_pos	  =	 original->y_pos+1.0f;
			    aux->pos_memo =					     0;
				original->a   =   GetDir(original,aux);
				aux->siguiente=			      original;

			  }
			   else
				{

				    aux->a	      =	            	   SUR;
					aux->wh		  =						10;
					aux->x_pos    =	   	   original->x_pos;
				    aux->y_pos    =	 original->y_pos+1.0f;
					aux->pos_memo =						 0;
					aux->siguiente=			 	  original;

				 }
			}
			 else
				{
				  aux->a	   = 		   		   	   NORTE;
				  aux->wh	   =					      10;
				  aux->x_pos   =		 	 original->x_pos;
				  aux->y_pos   =	   original->y_pos-1.0f;
				  aux->pos_memo=					       0;
				  aux->siguiente=			    	original;
				}

			break;

		}

		default:{break;}


	}








return aux;


}


SERPIENTE EliminarSerpienteMov(SERPIENTE original)
{
     if(original->siguiente==NULL)
     {
    	original=NULL;
    	return original;
     }
     else
    	 original->siguiente=EliminarSerpienteMov(original->siguiente);


return original;
}



SERPIENTE NuevaSerpienteMov(SERPIENTE original,DIRECCION dir)
{

    SERPIENTE nuevo=(SERPIENTE)malloc(sizeof(struct serpiente));


	switch(dir)
	{
	  case NORTE:{original=crearmovimiento(original,nuevo,dir); break;}
	  case  ESTE:{original=crearmovimiento(original,nuevo,dir); break;}
	  case OESTE:{original=crearmovimiento(original,nuevo,dir); break;}
	  case   SUR:{original=crearmovimiento(original,nuevo,dir); break;}

	  default:{break;}

	}


return original;

}



DIRECCION GetDir(SERPIENTE original,SERPIENTE aux)
{

	if(original->a == NORTE && aux->a == ESTE)return NORESTE;
	if(original->a == NORTE && aux->a == OESTE)return NOROESTE;

	if(original->a == SUR && aux->a == ESTE)return SURESTE;
	if(original->a == SUR && aux->a == OESTE)return SUROESTE;

	if(original->a == OESTE && aux->a == NORTE)return OESTENORTE;
	if(original->a == OESTE && aux->a == SUR)return OESTESUR;

	if(original->a == ESTE && aux->a == NORTE)return ESTENORTE;
	if(original->a == ESTE && aux->a == SUR)return ESTESUR;



 return original->a;
}

