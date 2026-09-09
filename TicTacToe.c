#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <string.h>

#define MAX_SIZE 10 // Maximum grid size
int procentage_of_win=0;//used by ai to determine the posibility of x to win
int ffsize,ffai,ffr,ffx,ff0;
char fboard[MAX_SIZE][MAX_SIZE];

//structure used to save data in a file
typedef struct  { 
    int size;
    int humam_ai;
    int rnd;
    int scorex;
    int score0;
    char table[MAX_SIZE][MAX_SIZE];
}file_struct;
//function used to save data
int save_file(char table1[MAX_SIZE][MAX_SIZE], int size1, int hum_ai, char nam[15],int r,int sx,int s0)
{
    FILE *my_file;
    file_struct t;
    int i,j;
    
    t.size=size1;
    t.humam_ai=hum_ai;
    t.rnd=r;
    t.scorex=sx;
    t.score0=s0;
     for(i=0;i<size1;i++)
        for(j=0;j<size1;j++)t.table[i][j]=table1[i][j];
    remove(nam); //deletes the file ussually tictock.dat; further version should ask for a new file when saving or opening
    my_file = fopen(nam, "wb");//wb opens file to write in binary mode

    if (my_file == NULL) {
                            perror("Error opening file");
                            return 1; // Indicate an error
                            }
    
    
     fwrite(&t, sizeof( file_struct), 1, my_file);
       
    fclose(my_file);
    return 0;
}


 //initialize the board  
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size,int r,int x_score,int y_score)
{             
	int i1,j1;

	printf("\n");
	for(j1=0; j1<size; j1++)printf("   %d",j1+1);
	printf("\n");

	for(i1=0; i1<size; i1++)
	{
		printf("%d|",i1+1);

		for(j1=0; j1<size; j1++)
		{
			board[i1][j1]=' ';
			printf("---|");
		}
		if(i1==0) printf("       ROUND:%d         X: %d         Y:%d",r,x_score,y_score);
		printf("\n");
	}

}

// function that prints the board, points of x, point for 0 and the score
void printBoard(char board[MAX_SIZE][MAX_SIZE], int size1,int r,int x_score,int y_score)
{       //function is call everytime a move is made
	int i1,j1;

	printf("\n");
	for(j1=0; j1<size1; j1++)printf("   %d",j1+1);
	printf("\n");

	for(i1=0; i1<size1; i1++)
	{
		printf("%d|",i1+1);

		for(j1=0; j1<size1; j1++)
		{
			printf("-");
			if(board[i1][j1]=='x')
			{
				printf("\033[32m"); //set color green for x
			}
			else if (board[i1][j1]=='0')
				printf("\033[33m"); //set color yellow for y
			else
				printf("\033[0m"); //reset colot to default white

			printf("%c",board[i1][j1]);
			printf("\033[0m"); //reset colot to default white
			printf("-|");
		}
		if(i1==0) printf("       ROUND:%d         X: %d         Y:%d",r,x_score,y_score);
		printf("\n");
	}
	return;
}

//check if a win has been reach for x or 0 on each line,column and diagonals
int checkWin(char board[MAX_SIZE][MAX_SIZE], int size)
{
	int val_to_returned=-1,i1,j1;   //return -1 is draw
	char compared_char;             //return 1 if x win    
                                    //return 2 if x win
	// checks win for each line;
	int win_foundl;
	i1=0;
	do       //initilize for each line
	{
		compared_char=board[i1][0];
		if(compared_char!=' ')
		{
			win_foundl=1;// assume we have a winner at the beggining of each line

			for(j1=0; j1<size; j1++)
				if(compared_char!=board[i1][j1]) win_foundl=0;
		} else
			win_foundl=0;
		i1++;
	} while ((i1<size)&&(win_foundl==0));

	if(win_foundl==1)
	{
		if (compared_char=='x') val_to_returned=1;
		else
			val_to_returned=2;
		return val_to_returned;
	}


	//checks for win on each column;
	int win_foundc;
	j1=0;
	do       //initilize for each line
	{
		compared_char=board[0][j1];
		if(compared_char!=' ')
		{
			win_foundc=1;// assume we have a winner at the beggining of each column

			for(i1=0; i1<size; i1++)
				if(compared_char!=board[i1][j1]) win_foundc=0;
		} else
			win_foundc=0;
		j1++;
	} while ((j1<size)&&(win_foundc==0));

	if(win_foundc==1)
	{
		if (compared_char=='x') val_to_returned=1;
		else
			val_to_returned=2;
		return val_to_returned;
	}


	//check win on diagonal 1;
	int win_foundd1;
	i1=0;
	j1=0;
	compared_char=board[i1][j1];
	win_foundd1=1;// assume we have a winner at the beggining of diagonal
	do
	{
		if(compared_char!=' ')
		{
			if(compared_char!=board[i1][j1]) win_foundd1=0;
		} else
			win_foundd1=0;

		i1++;
		j1++;
	} while (i1<size);

	if(win_foundd1==1)
	{
		if (compared_char=='x') val_to_returned=1;
		else
			val_to_returned=2;
		return val_to_returned;
	}
	
	//check for win on diagonal 2;
	int win_foundd2;
	i1=0;
    //j1=size;
		j1=size-1;
	compared_char=board[i1][j1];
	
	win_foundd2=1;// assume we have a winner at the beggining of diagonal
	do
	{
		if(compared_char!=' ')
		{
			if(compared_char!=board[i1][j1]) win_foundd2=0;
		} else
			win_foundd2=0;

		i1++;
		j1--;
	} while (i1<size);

	if(win_foundd2==1)
	{
		if (compared_char=='x') val_to_returned=1;
		else
			val_to_returned=2;
			
		return val_to_returned;
	}

	//return no winnner
	if((win_foundc==0)&&(win_foundl==0)&&(win_foundd1==0)&&(win_foundd2==0))
	{
		val_to_returned=-1;
		return val_to_returned;
	}

}

//function called for human vs human play
void playerMove(char table[MAX_SIZE][MAX_SIZE], int size,int newgame)  // function called if human to human is selected
{	int win,player=1,total_val; //total_val no of x and 0 togheter
	int runda=1,scorex=0,score0=0,h_m;
	int i,j,line, col,execcode;
	char inputchar,ch,save_and_quit;
	char file_name[15];
    
	do {
		win=-1;// no winner! will have a winner when win=1 or win=0;
		    if (newgame==0)
		            {  player=1;
		                 initializeBoard(table,size,runda,scorex,score0);
		                    total_val=0;
		            } 
		 if (newgame==1) 
		 {     
		      printf ("                   Previosely saved game!   ");
		      int total_x_saved=0,total_0_saved=0;
		        for(i=0;i<size;i++)
		            for(j=0;j<size;j++)
		            {
		                if (table[i][j]=='x') total_x_saved++;
		                if (table[i][j]=='0') total_0_saved++;
		            }
		       
		        //determine player no
		        
		        if (total_x_saved<=total_0_saved) player=1;
		        else player=2;
		        //determine total x and zero;
		        total_val=total_x_saved+total_0_saved;
		        //printf("totalval %d",total_val);
		 }
		do
		{
		    
			printf("\nTo quit enter negative numbers!\n\nLine Column player %d :",player);
			scanf("%d %d",&line,&col);

			fflush(stdin);

			if ((line>=1)&&(line<=size)&&(col>=1)&&(col<=size))
			{
				if (table[line-1][col-1]==' ')
				{
					if(player==1)
					{
						inputchar='x';
						player=2;
					} else
					{
						inputchar='0';
						player=1;
					}


					table[line-1][col-1]=inputchar;
					printBoard(table,size,runda,scorex,score0);
					win= checkWin(table,size);
					total_val++;
				}
				else printf("\nBox taken!");
			}

		} while((line>=0)&&(col>=0)&&(total_val!=size*size)&&(win==-1));
		
            //printf("\ntotal val%d ",total_val );
          
		if(win!=-1)
		    {	printf("\n WINNER %d!!!",win);
		        	if(win==1) scorex++;
		        	else score0++;
	    	}
		    printBoard(table,size,runda,scorex,score0);
		
		        if ( line>=0 && col>=0)
		          {
		            if(win==-1) printf("\nNO WINNER/NO POINTS!!!");

		            printf("\nNew game?... (Press 'q' and Enter to exit)");

	        	    while (getchar() != '\n' && getchar() != EOF); // Clears the input buffer
		            fflush(stdin);
		            ch=getchar();
		            //printf("You press %c!",ch);
		            if (ch != 'q' && ch != 'Q') newgame=0;
		            runda++;
		          }
	} while (ch != 'q' && ch != 'Q'&& line>=0 && col>=0);
	if ( line<0 || col<0)
	{   
	    char a;
	    printf("Do you want to save? Y/N");
	    while (getchar() != '\n' && getchar() != EOF); // Clears the input buffer
		fflush(stdin);
		a=getchar(); 
		printf("  You selected %c", a);
	    if((a=='y')||(a=='Y'))
	        {
	            printf("Saving...\n");
	            strcpy(file_name,"ticktock.dat");
	            h_m=0;
	            execcode=save_file( table,  size, h_m, file_name,runda,scorex,score0);
	        }
	}
	return;
}

// function called to decide ai defend or attack
int ai_defend_attack(char table[MAX_SIZE][MAX_SIZE], int size1,char c) //c could be x or 0
{
	int i,j,no_of_x_0,no_of_x_0_final,ret_val;
	int no_of_l_c_d; //stores the line or column or diagonal where the highes posibility of winning exist
	int filledboxes;
	
	procentage_of_win=0;
	//test the posibility of winning on one of the lines
		no_of_x_0_final=0;

	for(i=0; i<size1; i++)
	{
	    filledboxes=0;
		no_of_x_0=0;
		for(j=0; j<size1; j++)
		{
			if(table[i][j]==c) no_of_x_0++;
            	if(table[i][j]!=' ')filledboxes++;
		}
		if((no_of_x_0>no_of_x_0_final) && (filledboxes<size1))
		{
			no_of_x_0_final=no_of_x_0;
			no_of_l_c_d=i;
		}
	}
	        procentage_of_win = (no_of_x_0_final*100/size1);//no_of_x_0_final stores bieggest value of either x or 0, which one theres is more of on a line or column
	        ret_val = 100 + no_of_l_c_d; //returning code 100 plus the line on which might be a win
	   
	 	//test the posibility of winning on one of the columns
	no_of_x_0_final=0;
	
	for(j=0; j<size1; j++)
	{
	    filledboxes=0;
		no_of_x_0=0;
		for(i=0; i<size1; i++)
		{
			if(table[i][j]==c) no_of_x_0++;
			if(table[i][j]!=' ')filledboxes++;
		}
		
		if((no_of_x_0>no_of_x_0_final)&&(filledboxes<size1))
		{
			no_of_x_0_final=no_of_x_0;
			no_of_l_c_d=j;
		}
	}
	  
	    if(no_of_x_0_final*100/size1>procentage_of_win)
	    {
	    	procentage_of_win=no_of_x_0_final*100/size1;//Threat Calculation t count how many x or 0 are in a line.
	    	ret_val=200+no_of_l_c_d; //returning code 200 plus the column on which might be a win
	    }


	//test the posibility of winning on one of the diagonal 1
	filledboxes=0;
	no_of_x_0_final=0;
	i=0;
	j=0;
	do
	{
		if(table[i][j]==c)no_of_x_0_final++;
		if(table[i][j]!=' ')filledboxes++;
		i++;
		j++;
	} while(i<size1);

	if((no_of_x_0_final*100/size1>procentage_of_win)&&(filledboxes<size1))
	{
		procentage_of_win=no_of_x_0_final*100/size1;
		ret_val=301; //retur code 301  posible win on diagonal 1
	}

	//test the posibility of winning on one of the diagonal 2
	filledboxes=0;
	no_of_x_0_final=0;
	i=0;
	j=size1;
	do
	{
		if(table[i][j]==c)no_of_x_0_final++;
			if(table[i][j]!=' ')filledboxes++;
		i++;
		j--;
	} while(i<size1);
	
	if((no_of_x_0_final*100/size1>procentage_of_win)&&(filledboxes<size1))
	{
		procentage_of_win=no_of_x_0_final*100/size1;
		ret_val=302; //returning code 302  posible win on diagonal 2
	}
//printf("\n ai_defend_attack ret val %c   %d",c,ret_val);
	return ret_val;
}


//function called on human vs AI play
void aiMove(char table[MAX_SIZE][MAX_SIZE], int size1, int newgame)
{ //function calle for human against ai

	int win,player=1,total_val;
	int runda=1,scorex=0,score0=0;
	int line, col,ratio;
	int ai_result; 
	int ai_attack; //store the evaluation for 0
	int ai_defend;//store the evaluation for x
	char inputchar,ch,x0;
	int i,j,retv,procentage_of_win_0;

	do {
		  
	    	if (newgame==0)
		            {  player=1;
		                 initializeBoard(table,size1,runda,scorex,score0);
		                    total_val=0;
		            } 
		 if (newgame==1) 
		 {     
		      printf ("             Previosely saved  game!");
		      int total_x_saved=0,total_0_saved=0;
		        for(i=0;i<size1;i++)
		            for(j=0;j<size1;j++)
		            {
		                if (table[i][j]=='x') total_x_saved++;
		                if (table[i][j]=='0') total_0_saved++;
		            }
		       
		        //determine player no
		        if (total_x_saved<=total_0_saved) player=1;
		        else player=2;
		        //determine total x and zero;
		        total_val=total_x_saved+total_0_saved;
		 }
		    do
		    {
    			printf("\nLine  Column player %d :",player);
    			if (player==1) //player 1 is always human x imput
			    {	printf("    To save and exit enter netative numbers!   ");
				    scanf("%d %d",&line,&col);
				    fflush(stdin);
				    
			    }
			    else
			    {     //ai defends or attacks
                    
			        x0='0';
				    ai_attack=ai_defend_attack(table,size1,x0);
			        procentage_of_win_0=procentage_of_win;
			       // printf("\n0 probability %d",procentage_of_win_0);
			        
			        x0='x';
				    ai_defend= ai_defend_attack(table,size1,x0);
				   // printf("\nx probability %d",procentage_of_win);
				    
			       	ratio=100/size1;
				    
				    if( procentage_of_win<=ratio)
					        // generate line and colum beetwen 1 and size of the grid
				    {	do
					    {
						    line =  rand() % (size1-1) ;
						    col= rand() % (size1-1) ;
					     } while ((table[line][col]=='x')||(table[line][col]=='0'));
					    
				    }
				    else
				    { 
					   if (procentage_of_win_0>=65) //level of dificulty can be change here
					        ai_result=ai_attack;
					   else
					        ai_result=ai_defend;
					    
					    retv=ai_result/100;
					    i=0;
					    j=0;
                        
                        //decode the returning code of function ai_defend_attack
					    if (retv==1) 
				        	{	line=ai_result%100;//here i get the line number
					    	j=-1;
					    	    do {j++;} while ((table[line][j]!=' ')&&(j<size1)&&(j<size1));
						    col=j;
					        }

					   if (retv==2)
					        {	col=ai_result%200;//i get the column number
						        i=-1;
						        do
						            {
						            	i++;
						             } while ((table[i][col]!=' ')&&(i<size1)&&(j<size1));
						        line=i;
					        }

					   if (retv==3)
					        {
						        if(ai_result%300==1)
						            {	//diagonala 1;
						            	i=-1;
						                j=-1;
							            do
							            {
								            i++;
							            	j++;
							            } while ((table[i][j]!=' ')&&(i<size1)&&(j<size1));
							                line=i;
							                col=j;
						            }
					        	if(ai_result%300==2)
					            	{	//diagonala 2;
						            	i=-1;
						            	j=size1;
						            	do
						            	{
							            	i++;
							            	j--;
							            } while((table[i][j]!=' ')&&(i<size1));
							                line=i;
							                col=j;
						            } 
				        	} 

				        }
				printf ("\nAI x: %d   AI y:%d",line+1, col+1);
			
			    }//else for player ==1;
			    
			     if(player==1)
			    {   
			        if ((line>=0)&&(col>=0))
				        {         //inputchar='x';
			    	              //  player=2;
				                if(table[line-1][col-1]==' ')
				                {   inputchar='x';
			    	                player=2;
			    		            table[line-1][col-1]=inputchar;
			    		            printBoard(table,size1,runda,scorex,score0);
				                    win= checkWin(table,size1);
			    		            total_val++;
				                }
				                else printf("Box taken!!");
				        }
			    	
			    }
                else
			    	{
				        inputchar='0';
				        player=1;
				        if(table[line][col]==' ')
				            {
				   	               table[line][col]=inputchar;
				   	               printBoard(table,size1,runda,scorex,score0);
				                    win= checkWin(table,size1);
					               total_val++;
			    	        } else printf("Box taken!!");
			        }

			   } while((line>=0)&&(col>=0)&&(total_val!=size1*size1)&&(win==-1));
            
            
		if((line>=0)&&(col>=0))
		  {          if(win!=-1)
		            {	printf("\nWINNER %d!!!",win);
		            	if(win==1) scorex++;
	            		else score0++;
		            }
		            printBoard(table,size1,runda,scorex,score0);//function call to update the score
		
		            if(win==-1) printf("\nNO WINNER/NO POINTS!!!");

		            printf("New Game?... (Press 'q' and Enter to exit)");

		            while (getchar() != '\n' && getchar() != EOF); // Clears the input buffer
		            fflush(stdin);
		            ch=getchar();
		            //printf("You press %c!",ch);
		            if (ch != 'q' && ch != 'Q') newgame=0;
		            runda++;
		  }
	} while ((ch != 'q' && ch != 'Q')&&(line>=0)&&(col>=0));
	
	if ((line<0)||(col<0))
	{   
	    int h_m=1,execcode;
	    char file_name[15], a;
	    printf(" Do you want to save save? Y/N ");
	    while (getchar() != '\n' && getchar() != EOF); // Clears the input buffer
		fflush(stdin);
		            a=getchar();
		            printf("  You selected %c", a);
	    if ((a=='y') || (a=='Y'))
	        {
	            printf("Saving...\n");
	            strcpy(file_name,"ticktock.dat");
	            execcode=save_file( table,  size1, h_m, file_name,runda,scorex,score0);
	        }
	}
	return ;

}


int open_file(char table1[MAX_SIZE][MAX_SIZE], int size, int hum_ai, char nam[15])
{
    FILE *my_file;
     file_struct t;
    int i,j;

    my_file = fopen("ticktock.dat", "r"); // Open in binary read mode
    if (my_file == NULL) {
                             perror("Error opening file");
                              return 1;
                         }
    
   
    fread(&t , sizeof(file_struct),1,my_file);
    ffsize=t.size;
    ffai= t.humam_ai;
    ffr=t.rnd;
    ffx=t.scorex;
    ff0=t.score0;
     //printf("size in open file %d",ffsize); 
        for(i=0;i<ffsize;i++)
              for(j=0;j<ffsize;j++) fboard[i][j]=t.table[i][j];
          
        printf("DONE reading!\n");
     fclose(my_file);
}

//small menu option _ialization
int init_menu(int value)
{   int h_m,new_game;
    int gsize,s;
    int i,j;
	int modeai;
	int execcode;
	char file_name[15];
	char table1[MAX_SIZE][MAX_SIZE];
	int runda,scorex,score0;
	strcpy(file_name,"ticktock.dat");
	 
    if (value==1)//for new game
	      {  
	            do
	                {	printf("\nGrid size ");
		            scanf("%d",&gsize);
                	//gsize=4;
		            if((gsize<3)||(gsize>10)) printf(" Size must be >=3 <=10");
	                } while ((gsize<3)||(gsize>10));
    	            fflush(stdin);


	                printf("1: AI Mode \n2: Human \nPress 1 or another key!...and ENTER ");
	                scanf("%d",&modeai);
	
                    //modeai=1;
	                if(modeai==1)
	                {
	                	printf("        AI mode selected!\n");
		                srand(time(NULL));
		                int newgame=0;
		                aiMove(table1,gsize,newgame);
	                }
	                else
                	{
		                printf("        Human opponent selected!\n");
		                new_game=0;
		                playerMove(table1,gsize,new_game);
	                }
	      }//init =0int gsize;
	
	if(value==2)// for game loaded from file
            
            {
                execcode=open_file( table1,  s, h_m, file_name);
               // printf("size : %d    ai:%d\n", ffsize, ffai);
                for(i=0;i<ffsize;i++) for(j=0;j<ffsize;j++)table1[i][j]=fboard[i][j];
               
                    runda=ffr;scorex=ffx;score0=ff0;
                    printBoard(table1,ffsize,runda,scorex,score0);
                    if (ffai==0)//human player saved
                    {
                         printf("        Human opponent selected!\n");
                         new_game=1;
                         gsize=ffsize;
		                playerMove(table1,gsize,new_game);
                    }
                    if (ffai==1) //ai player saved
                    {
                         printf("        AI opponent selected!\n");
                         new_game=1;
                         gsize=ffsize;
		                aiMove(table1,gsize,new_game);
                    }
                    //call the function for playerMove or aimove
            }
}

int main()
{	int gsize,v;
	int modeai,init_ret_val;
	char table1[MAX_SIZE][MAX_SIZE];

		printf("                TIC-TOCK\n");
	do 
   { printf("\n\n1. New game\n2. Load Game\n3. Exit\nSelect an option ");
    scanf("%d",&v);
    init_ret_val=init_menu(v);
   }while(v!=3) ;
 	return 0;
}