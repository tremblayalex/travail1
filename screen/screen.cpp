#include "screen.h"

/* ---------------------------------------------------------------------------*/
/* Fonction qui sert � effacer l'�cran en utilisant la couleur du dernier     */
/* TextBackground effectu�. Replace le curseur en haut � gauche               */
/* ---------------------------------------------------------------------------*/
void ClrScr()
{
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
	HANDLE ScreenHandle;
	COORD Home={0,0};
	DWORD N=0;
	ScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//pour avoir de l'information sur la fen�tre (ses dimensions)
	GetConsoleScreenBufferInfo(ScreenHandle,&ScreenInfo); 
	//efface les caract�res de l'�cran
	FillConsoleOutputCharacter(ScreenHandle,' ',ScreenInfo.dwSize.X * ScreenInfo.dwSize.Y,Home,&N);
	//remplit l'�cran avec la couleur du dernier TextBackground
	FillConsoleOutputAttribute(ScreenHandle,ScreenInfo.wAttributes,ScreenInfo.dwSize.X * ScreenInfo.dwSize.Y,Home,&N);
	Gotoxy(0,0);
}

/* ---------------------------------------------------------------------------*/
/* Fonction qui sert � effacer la ligne sur laquelle le curseur est plac�     */
/* L'effacement se produit � partir de la position du curseur jusqu'� la fin de la ligne*/
/* La couleur utilis�e est celle du dernier TextBackground effectu�           */
/* ---------------------------------------------------------------------------*/
void ClrEol()
{
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
	HANDLE ScreenHandle;
	COORD Home={0,0};
	COORD Pos={0,0};
	DWORD N=0;
	ScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//pour avoir de l'information sur la fen�tre (positions actuelles du curseur)
	GetConsoleScreenBufferInfo(ScreenHandle,&ScreenInfo); 
	Home = ScreenInfo.dwCursorPosition;
	Pos.X = 80 - ScreenInfo.dwCursorPosition.X;
	//efface les caract�res � partir de la position du curseur jusqu'� la fin de la ligne
	FillConsoleOutputCharacter(ScreenHandle,' ',Pos.X,Home,&N);
	//remplit avec la couleur du dernier TextBackGround
	FillConsoleOutputAttribute(ScreenHandle,ScreenInfo.wAttributes,Pos.X,Home,&N);
}

/* ---------------------------------------------------------------------------*/
/* Fonction qui sert � effacer l'�cran � partir de la position du curseur    */
/* jusqu'� la fin de l'�cran en utilisant la couleur du dernier TextBackGround effectu� */
/* Le curseur est replac� en haut � gauche                                    */
/* ---------------------------------------------------------------------------*/
void ClrEoscr()
{
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
	HANDLE ScreenHandle;
	COORD Home;
	LPDWORD N=0;
	ScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//pour avoir de l'information sur la fen�tre (positions actuelles du curseur et dimensions de l'�cran)
	GetConsoleScreenBufferInfo(ScreenHandle,&ScreenInfo); 
	Home = ScreenInfo.dwCursorPosition;
	//efface � partir de la position du curseur jusqu'� la fin de l'�cran
	FillConsoleOutputCharacter(ScreenHandle,' ',ScreenInfo.dwSize.X * ScreenInfo.dwSize.Y,Home,N);
	//remplit avec la couleur du dernier TextBackground
	FillConsoleOutputAttribute(ScreenHandle,ScreenInfo.wAttributes,ScreenInfo.dwSize.X * ScreenInfo.dwSize.Y,Home,N);
	Gotoxy(0,0);
}

/* ---------------------------------------------------------------------------*/
/* Fonction qui place le curseur aux positions sp�cifi�es                     */
/* InX et InY: positions en X et en Y o� il faut placer le curseur            */
/* ---------------------------------------------------------------------------*/
void Gotoxy(int InX, int InY)
{
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
	HANDLE ScreenHandle;
	ScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//il faut indiquer � quelles positions le curseur doit se placer
	ScreenInfo.dwCursorPosition.X = InX;
	ScreenInfo.dwCursorPosition.Y = InY;
	//place le curseur � l'endroit indiqu�
	SetConsoleCursorPosition(ScreenHandle,ScreenInfo.dwCursorPosition);
}

/* ---------------------------------------------------------------------------*/
/* Fonction qui modifie la couleur du prochain texte � afficher               */
/* InFontcolor : couleur d�sir�e pour le texte                                  */
/* ---------------------------------------------------------------------------*/
void TextColor(int InFontcolor)
{
   HANDLE  ScreenHandle;
   CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
   int Color;
   ScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   //pour connaitre les couleurs actuelles
   GetConsoleScreenBufferInfo(ScreenHandle,&ScreenInfo); 
   //les instructions suivantes servent � modifier la couleur du texte sans modifier la couleur de fond
   Color = ScreenInfo.wAttributes & 112; 
   Color = Color | InFontcolor; 
   //modifie la couleur d'affichage et de fond des prochaines instructions
   SetConsoleTextAttribute(ScreenHandle,Color);
}

/* ---------------------------------------------------------------------------*/
/* Fonction qui modifie la couleur de fond du prochain texte � afficher       */
/* InBackground: couleur � utiliser pour le fond                              */
/* ---------------------------------------------------------------------------*/
void TextBackground(int InBackground)
{
   HANDLE  ScreenHandle;
   CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
   int Color;
   ScreenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   //pour connaitre les couleurs actuelles
   GetConsoleScreenBufferInfo(ScreenHandle,&ScreenInfo); 
   //les instructions suivantes servent � modifier la couleur de fond tout en gardant la couleur de texte actuelle 
   Color = ScreenInfo.wAttributes & 15; 
   InBackground = InBackground << 4;  //il faut placer la couleur aux bits 5-6-7
   Color = Color | InBackground; 
   //modifie la couleur d'affichage et de fond des prochaines instructions
   SetConsoleTextAttribute(ScreenHandle,Color);
}