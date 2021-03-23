//现存问题：轮转庄家 

#include<bits/stdc++.h>
#define MAXN 1000005
#define LL long long

using namespace std;

struct Utility_Node{/*Describe the absolute value of one combination*/
	int Type;/*from 9-1, represent: Straight_Flush, Four_of_a_Kind, Full_House, Flush, Straight, Three_of_a_Kind, Two_Pairs, One_Pair, High_Card*/
	int Value_1,Value_2,Value_3,Value_4,Value_5;/*the 5 Values represent the 5 top cards in the order of importance*/
	
	Utility_Node(int Type=0,int Value_1=0,int Value_2=0,int Value_3=0,int Value_4=0,int Value_5=0):
		Type(Type),Value_1(Value_1),Value_2(Value_2),Value_3(Value_3),Value_4(Value_4),Value_5(Value_5){} 
		
	bool operator < (const Utility_Node &State) const{
		if(Type!=State.Type) return Type<State.Type;
		if(Value_1!=State.Value_1) return Value_1<State.Value_1;
		if(Value_2!=State.Value_2) return Value_2<State.Value_2;
		if(Value_3!=State.Value_3) return Value_3<State.Value_3;
		if(Value_4!=State.Value_4) return Value_4<State.Value_4;
		if(Value_5!=State.Value_5) return Value_5<State.Value_5;
	}
};

struct State_Node{/*Current Cards presented*/
	int Spade,Heart,Diamond,Club;/*Four suits are changed into 4 integers. When changed to binary, there will be 13 digits. From the highest to lowest, represent A-K-Q-...-3-2*/
	
	State_Node(int Spade=0,int Heart=0,int Diamond=0,int Club=0):
		Spade(Spade),Heart(Heart),Diamond(Diamond),Club(Club){}
};

struct Player_Node{
	char Suit_1,Suit_2;
	int Number_1,Number_2;
	
	Player_Node(char Suit_1='s',char Suit_2='s',int Number_1=0,int Number_2=0):
		Suit_1(Suit_1),Suit_2(Suit_2),Number_1(Number_1),Number_2(Number_2){}
}; 

struct Card_Node{
	char Suit;
	int Number;
	
	Card_Node(char Suit='s',int Number=0):
		Suit(Suit),Number(Number){}
}; 

struct Outcome_Node{
	int Player,Value;
	
	Outcome_Node(int Player=0,int Value=0):
		Player(Player),Value(Value){}
};

State_Node Initiate(); 
Utility_Node Utility(State_Node State);/*Calculate the absolute value of the State*/
void Output(Utility_Node Utility_Value); 
char Output_int_to_char(int Number_of_the_Card);
bool Self_Checking_System(Utility_Node Utility_Value);
State_Node Combining_Hand_and_Board(Player_Node Player,State_Node State);

Utility_Node Straight_Flush_Verification(State_Node State);/*Verify the Existence of Straight_Flush*/
Utility_Node Four_of_a_Kind_Verification(State_Node State);/*Verify the Existence of Four_of_a_Kind*/
Utility_Node Full_House_Verification(State_Node State);/*Verify the Existence of Full_House*/
Utility_Node Flush_Verification(State_Node State);/*Verify the Existence of Flush*/
Utility_Node Straight_Verification(State_Node State);/*Verify the Existence of Straight*/
Utility_Node Three_of_a_Kind_Verification(State_Node State);/*Verify the Existence of Three_of_a_Kind*/
Utility_Node Two_Pairs_Verification(State_Node State);/*Verify the Existence of Two_Pairs*/
Utility_Node One_Pair_Verification(State_Node State);/*Verify the Existence of One_Pair*/
Utility_Node High_Card_Verification(State_Node State);/*Verify the Existence of High_Card*/ 

Utility_Node Flush_Verification_Secondary_Single_Color_Verification(int Single_State);//return Utility_Value of the Flush if there is any, Otherwise return 0
Utility_Node High_Card_Secondary_Verification(int Single_State);//return Utility_Value of the High_Card


Outcome_Node Game_Structure();
Player_Node Initiate_Player_State(State_Node &Unavailable_State,State_Node &Board_State,int Board_or_Not);
Card_Node Initiate_Card(State_Node &Unavailable_State,State_Node &Board_State,int Board_or_Not);
Outcome_Node Outcome_Calculation(int End_State,int Stack_1,int Stack_2);


Outcome_Node Game_Structure()
{
	cout<<"New Game Started!!!"<<endl<<endl;
	
	State_Node Unavailable_State=State_Node(0,0,0,0);
	State_Node Board_State=State_Node(0,0,0,0);
	
	int Stack_1=200-2;
	int Stack_2=200-1;
	
	int Preflop_Stack_1=2;
	int Preflop_Stack_2=1;
	
	int Flop_Stack_1=0;
	int Flop_Stack_2=0;
	
	int Turn_Stack_1=0;
	int Turn_Stack_2=0;
	
	int River_Stack_1=0;
	int River_Stack_2=0;
	
	int Bet,End_State=0;
	
	Player_Node Player_1=Initiate_Player_State(Unavailable_State,Board_State,0);
	Player_Node Player_2=Initiate_Player_State(Unavailable_State,Board_State,0);
	
//	Player_Node Player_1=Player_Node('s','c',13,13);
//	Player_Node Player_2=Player_Node('s','c',8,8);
	
	cout<<"Player_1 Cards: "<<Output_int_to_char(Player_1.Number_1)<<Player_1.Suit_1<<" "<<Output_int_to_char(Player_1.Number_2)<<Player_1.Suit_2<<endl;
	cout<<"Player_2 Cards: "<<Output_int_to_char(Player_2.Number_1)<<Player_2.Suit_1<<" "<<Output_int_to_char(Player_2.Number_2)<<Player_2.Suit_2<<endl;
	cout<<endl;
	
	cout<<"Player_2 Small Blind: 1"<<endl;
	cout<<"Player_1 Big Blind: 2"<<endl;
	
	while(Stack_1 || Stack_2)
	{
		cout<<"Player_2 Action: ";
		cin>>Bet;
		if(Bet==0) {End_State=1;break;}
		Stack_2-=Bet-Preflop_Stack_2;
		Preflop_Stack_2=Bet;
		if(Stack_1==Stack_2 && Preflop_Stack_2!=2) break;
		
		cout<<"Player_1 Action: ";
		cin>>Bet;
		if(Bet==0) {End_State=2;break;}
		Stack_1-=Bet-Preflop_Stack_1;
		Preflop_Stack_1=Bet;
		if(Stack_1==Stack_2) break;
	}
	
	if(End_State) return Outcome_Calculation(End_State,Stack_1,Stack_2);
	
	cout<<endl;
	cout<<"Player 1 Remaining Stack: "<<Stack_1<<endl;
	cout<<"Player 2 Remaining Stack: "<<Stack_2<<endl;
	cout<<endl;
	
	Card_Node Flop_1=Initiate_Card(Unavailable_State,Board_State,1);
	Card_Node Flop_2=Initiate_Card(Unavailable_State,Board_State,1);
	Card_Node Flop_3=Initiate_Card(Unavailable_State,Board_State,1);
	
	cout<<"Flop: ";
	cout<<Output_int_to_char(Flop_1.Number)<<Flop_1.Suit<<" ";
	cout<<Output_int_to_char(Flop_2.Number)<<Flop_2.Suit<<" ";
	cout<<Output_int_to_char(Flop_3.Number)<<Flop_3.Suit<<" ";
	cout<<endl;
	
	while(Stack_1 || Stack_2)
	{
		cout<<"Player_1 Action: ";
		cin>>Bet;
		if(Bet==0 && Flop_Stack_2!=0) {End_State=2;break;}
		Stack_1-=Bet-Flop_Stack_1;
		Flop_Stack_1=Bet;
		if(Stack_1==Stack_2 && Flop_Stack_2!=0) break;
		
		cout<<"Player_2 Action: ";
		cin>>Bet;
		if(Bet==0 && Flop_Stack_1!=0) {End_State=1;break;}
		Stack_2-=Bet-Flop_Stack_2;
		Flop_Stack_2=Bet;
		if(Stack_1==Stack_2 || (Flop_Stack_1==0 && Flop_Stack_2==0)) break;
	}
	
	if(End_State) return Outcome_Calculation(End_State,Stack_1,Stack_2);
	
	cout<<endl;
	cout<<"Player 1 Remaining Stack: "<<Stack_1<<endl;
	cout<<"Player 2 Remaining Stack: "<<Stack_2<<endl;
	cout<<endl;
	
	Card_Node Turn_1=Initiate_Card(Unavailable_State,Board_State,1);
	
	cout<<"Turn: ";
	cout<<Output_int_to_char(Flop_1.Number)<<Flop_1.Suit<<" ";
	cout<<Output_int_to_char(Flop_2.Number)<<Flop_2.Suit<<" ";
	cout<<Output_int_to_char(Flop_3.Number)<<Flop_3.Suit<<" ";
	cout<<Output_int_to_char(Turn_1.Number)<<Turn_1.Suit<<" ";
	cout<<endl;
	
	while(Stack_1 || Stack_2)
	{
		cout<<"Player_1 Action: ";
		cin>>Bet;
		if(Bet==0 && Turn_Stack_2!=0) {End_State=2;break;}
		Stack_1-=Bet-Turn_Stack_1;
		Turn_Stack_1=Bet;
		if(Stack_1==Stack_2 && Turn_Stack_2!=0) break;
		
		cout<<"Player_2 Action: ";
		cin>>Bet;
		if(Bet==0 && Turn_Stack_1!=0) {End_State=1;break;}
		Stack_2-=Bet-Turn_Stack_2;
		Turn_Stack_2=Bet;
		if(Stack_1==Stack_2 || (Turn_Stack_1==0 && Turn_Stack_2==0)) break;
	}
	
	if(End_State) return Outcome_Calculation(End_State,Stack_1,Stack_2);
	
	cout<<endl;
	cout<<"Player 1 Remaining Stack: "<<Stack_1<<endl;
	cout<<"Player 2 Remaining Stack: "<<Stack_2<<endl;
	cout<<endl;
	
	Card_Node River_1=Initiate_Card(Unavailable_State,Board_State,1);
	
	cout<<"River: ";
	cout<<Output_int_to_char(Flop_1.Number)<<Flop_1.Suit<<" ";
	cout<<Output_int_to_char(Flop_2.Number)<<Flop_2.Suit<<" ";
	cout<<Output_int_to_char(Flop_3.Number)<<Flop_3.Suit<<" ";
	cout<<Output_int_to_char(Turn_1.Number)<<Turn_1.Suit<<" ";
	cout<<Output_int_to_char(River_1.Number)<<River_1.Suit<<" ";
	cout<<endl;
	
	while(Stack_1 || Stack_2)
	{
		cout<<"Player_1 Action: ";
		cin>>Bet;
		if(Bet==0 && River_Stack_2!=0) {End_State=2;break;}
		Stack_1-=Bet-River_Stack_1;
		River_Stack_1=Bet;
		if(Stack_1==Stack_2 && River_Stack_2!=0) break;
		
		cout<<"Player_2 Action: ";
		cin>>Bet;
		if(Bet==0 && River_Stack_1!=0) {End_State=1;break;}
		Stack_2-=Bet-River_Stack_2;
		River_Stack_2=Bet;
		if(Stack_1==Stack_2 || (Turn_Stack_1==0 && River_Stack_2==0)) break;
	}
	
	if(End_State) return Outcome_Calculation(End_State,Stack_1,Stack_2);
	
	State_Node Player_1_State=Combining_Hand_and_Board(Player_1,Board_State);
	State_Node Player_2_State=Combining_Hand_and_Board(Player_2,Board_State);
	
	Utility_Node Player_1_Utility=Utility(Player_1_State);
	Utility_Node Player_2_Utility=Utility(Player_2_State);
	
//	cout<<Player_1_State.Spade<<" "<<Player_1_State.Heart<<" "<<Player_1_State.Diamond<<" "<<Player_1_State.Club<<endl;
//	cout<<Player_2_State.Spade<<" "<<Player_2_State.Heart<<" "<<Player_2_State.Diamond<<" "<<Player_2_State.Club<<endl;
//	cout<<Player_1_Utility.Type<<" "<<Player_2_Utility.Type<<endl;
//	cout<<Unavailable_State.Spade<<" "<<Unavailable_State.Heart<<" "<<Unavailable_State.Diamond<<" "<<Unavailable_State.Club<<endl;
//	cout<<Board_State.Spade<<" "<<Board_State.Heart<<" "<<Board_State.Diamond<<" "<<Board_State.Club<<endl;
	
	if(Player_1_Utility.Type==Player_2_Utility.Type &&
		Player_1_Utility.Value_1==Player_2_Utility.Value_1 &&
		Player_1_Utility.Value_2==Player_2_Utility.Value_2 &&
		Player_1_Utility.Value_3==Player_2_Utility.Value_3 &&
		Player_1_Utility.Value_4==Player_2_Utility.Value_4 &&
		Player_1_Utility.Value_5==Player_2_Utility.Value_5) return Outcome_Node(0,0);
	else if(Player_1_Utility<Player_2_Utility) return Outcome_Node(2,200-Stack_1);
	else return Outcome_Node(1,200-Stack_2);
}

Player_Node Initiate_Player_State(State_Node &Unavailable_State,State_Node &Board_State,int Board_or_Not)
{
	Card_Node Card_1=Initiate_Card(Unavailable_State,Board_State,0);
	Card_Node Card_2=Initiate_Card(Unavailable_State,Board_State,0);
	
	return Player_Node(Card_1.Suit,Card_2.Suit,Card_1.Number,Card_2.Number);
}

Card_Node Initiate_Card(State_Node &Unavailable_State,State_Node &Board_State,int Board_or_Not)
{
	char Suit;
	int Number,Suit_int;
	
	while(1)
	{
		Number=rand()%13+1;
		Suit_int=rand()%4+1;
		
		if(Suit_int==1) Suit='s';
		if(Suit_int==2) Suit='h';	
		if(Suit_int==3) Suit='d';	
		if(Suit_int==4) Suit='c';	
		
		if(Suit_int==1 && (Unavailable_State.Spade&(1<<(Number-1)))!=0) continue;
		if(Suit_int==2 && (Unavailable_State.Heart&(1<<(Number-1)))!=0) continue;	
		if(Suit_int==3 && (Unavailable_State.Diamond&(1<<(Number-1)))!=0) continue;	
		if(Suit_int==4 && (Unavailable_State.Club&(1<<(Number-1)))!=0) continue;
		
		if(Suit_int==1) Unavailable_State.Spade+=(1<<(Number-1));
		if(Suit_int==2) Unavailable_State.Heart+=(1<<(Number-1));	
		if(Suit_int==3) Unavailable_State.Diamond+=(1<<(Number-1));	
		if(Suit_int==4) Unavailable_State.Club+=(1<<(Number-1));
		
		if(Suit_int==1 && Board_or_Not) Board_State.Spade+=(1<<(Number-1));
		if(Suit_int==2 && Board_or_Not) Board_State.Heart+=(1<<(Number-1));	
		if(Suit_int==3 && Board_or_Not) Board_State.Diamond+=(1<<(Number-1));	
		if(Suit_int==4 && Board_or_Not) Board_State.Club+=(1<<(Number-1));
		
		break;
	}
	return Card_Node(Suit,Number);
}

Outcome_Node Outcome_Calculation(int End_State,int Stack_1,int Stack_2)
{
	if(End_State==1) return Outcome_Node(End_State,200-Stack_2);
	else return Outcome_Node(End_State,200-Stack_1);
}

State_Node Combining_Hand_and_Board(Player_Node Player,State_Node State)
{
	char Suit_1=Player.Suit_1,Suit_2=Player.Suit_2;
	int Number_1=Player.Number_1,Number_2=Player.Number_2;
	
	if(Suit_1=='s') State.Spade+=(1<<(Number_1-1));
	if(Suit_1=='h') State.Heart+=(1<<(Number_1-1));	
	if(Suit_1=='d') State.Diamond+=(1<<(Number_1-1));	
	if(Suit_1=='c') State.Club+=(1<<(Number_1-1));
	
	if(Suit_2=='s') State.Spade+=(1<<(Number_2-1));
	if(Suit_2=='h') State.Heart+=(1<<(Number_2-1));	
	if(Suit_2=='d') State.Diamond+=(1<<(Number_2-1));	
	if(Suit_2=='c') State.Club+=(1<<(Number_2-1));
	
	return State;
}


State_Node Initiate()
{
	int Cards/*How many cards?*/,Spade=0,Heart=0,Diamond=0,Club=0;
	char Number_of_the_Card_in_char/**/, Suit_of_the_Card_in_char/**/;
	int Number_of_the_Card_in_int=0/**/, Suit_of_the_Card_in_int=0/**/;
	cin>>Cards;
	
	while(Cards--)
	{
		//For each hand, first input the number of howmany cards you know x
		//after that, input x cards with these rules:
		//for each card, first input the number, then input the suit
		//the number includes: A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2
		//the suit includes: s, h, d, c
		//for example, if you want to input the 10 of spade, just input Ts
		//seperate each card by using a space
		//for example, if you want to in put A of spade and 4 of club, just input As 4c
		//
		//here is a standered input:
		//7
		//6s 6c 6h 7d 9h Tc As
		//4 5 5 5 13 9
		//
		
		cin>>Number_of_the_Card_in_char>>Suit_of_the_Card_in_char;
		
		if(Number_of_the_Card_in_char=='A') Number_of_the_Card_in_int=(1<<12);
		else if(Number_of_the_Card_in_char=='K') Number_of_the_Card_in_int=(1<<11);
		else if(Number_of_the_Card_in_char=='Q') Number_of_the_Card_in_int=(1<<10);
		else if(Number_of_the_Card_in_char=='J') Number_of_the_Card_in_int=(1<<9);
		else if(Number_of_the_Card_in_char=='T') Number_of_the_Card_in_int=(1<<8);
		else Number_of_the_Card_in_int=(1<<(Number_of_the_Card_in_char-'1'-1));
		
		if(Suit_of_the_Card_in_char=='s') Spade+=Number_of_the_Card_in_int;
		else if(Suit_of_the_Card_in_char=='h') Heart+=Number_of_the_Card_in_int;
		else if(Suit_of_the_Card_in_char=='d') Diamond+=Number_of_the_Card_in_int;
		else if(Suit_of_the_Card_in_char=='c') Club+=Number_of_the_Card_in_int;
	}
	
	return State_Node(Spade,Heart,Diamond,Club); 
}

Utility_Node Utility(State_Node State)
{
	Utility_Node Utility_Value;
	
	Utility_Value=Straight_Flush_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=Four_of_a_Kind_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=Full_House_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=Flush_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=Straight_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=Three_of_a_Kind_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=Two_Pairs_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=One_Pair_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	Utility_Value=High_Card_Verification(State);
	if(Utility_Value.Type) return Utility_Value;
	
	return Utility_Node(0,0,0,0,0,0);
}

void Output(Utility_Node Utility_Value)
{
	int Type=Utility_Value.Type;
	int Value_1=Utility_Value.Value_1;
	int Value_2=Utility_Value.Value_2;
	int Value_3=Utility_Value.Value_3;
	int Value_4=Utility_Value.Value_4;
	int Value_5=Utility_Value.Value_5;
	
	if(Type==0) {cout<<"Error"<<endl; return;}
	if(Type==9) cout<<"Straight_Flush: ";
	if(Type==8) cout<<"Four_of_a_Kind: ";
	if(Type==7) cout<<"Full_House: ";
	if(Type==6) cout<<"Flush: ";
	if(Type==5) cout<<"Straight: ";
	if(Type==4) cout<<"Three_of_a_Kind: ";
	if(Type==3) cout<<"Two_Pairs: ";
	if(Type==2) cout<<"One_Pair: ";
	if(Type==1) cout<<"High_Card: ";
	
	cout<<Output_int_to_char(Value_1)<<Output_int_to_char(Value_2)<<Output_int_to_char(Value_3)<<Output_int_to_char(Value_4)<<Output_int_to_char(Value_5)<<endl;
	
	return;
}

char Output_int_to_char(int Number_of_the_Card)
{
	if(Number_of_the_Card==13) return 'A';
	else if(Number_of_the_Card==12) return 'K';
	else if(Number_of_the_Card==11) return 'Q';
	else if(Number_of_the_Card==10) return 'J';
	else if(Number_of_the_Card==9) return 'T';
	return char('1'+(Number_of_the_Card));
}

bool Self_Checking_System(Utility_Node Utility_Value)
{
	int Type,Value_1,Value_2,Value_3,Value_4,Value_5;
	cin>>Type>>Value_1>>Value_2>>Value_3>>Value_4>>Value_5;
	Utility_Node Valid_Answer=Utility_Node(Type,Value_1,Value_2,Value_3,Value_4,Value_5);
	if(Utility_Value.Type==Valid_Answer.Type && Utility_Value.Value_1==Valid_Answer.Value_1 && Utility_Value.Value_2==Valid_Answer.Value_2 && Utility_Value.Value_3==Valid_Answer.Value_3 && Utility_Value.Value_4==Valid_Answer.Value_4 && Utility_Value.Value_5==Valid_Answer.Value_5) {cout<<"Correct"<<endl; return 1;}
	else {cout<<"Wrong"<<endl; return 0;}
}



Utility_Node Straight_Flush_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int Spade_Straight_Flush=max(Spade&(Spade<<1)&(Spade<<2)&(Spade<<3)&(Spade<<4),Spade&(Spade<<1)&(Spade<<2)&(Spade<<3)&(Spade>>9));/**/
	int Heart_Straight_Flush=max(Heart&(Heart<<1)&(Heart<<2)&(Heart<<3)&(Heart<<4),Heart&(Heart<<1)&(Heart<<2)&(Heart<<3)&(Heart>>9));
	int Diamond_Straight_Flush=max(Diamond&(Diamond<<1)&(Diamond<<2)&(Diamond<<3)&(Diamond<<4),Diamond&(Diamond<<1)&(Diamond<<2)&(Diamond<<3)&(Diamond>>9));
	int Club_Straight_Flush=max(Club&(Club<<1)&(Club<<2)&(Club<<3)&(Club<<4),Club&(Club<<1)&(Club<<2)&(Club<<3)&(Club>>9));
	
	int Straight_Flush=max(max(Spade_Straight_Flush,Heart_Straight_Flush),max(Diamond_Straight_Flush,Club_Straight_Flush));/**/

	int Value_place_First=0/**/;
	
	while(Straight_Flush)/**/
	{
		Value_place_First++;
		Straight_Flush=Straight_Flush>>1;
	}
	
	if(!Value_place_First) return Utility_Node(0,0,0,0,0,0);
	
	if(Value_place_First==4) return Utility_Node(9,4,3,2,1,13);
	else return Utility_Node(9,Value_place_First,Value_place_First-1,Value_place_First-2,Value_place_First-3,Value_place_First-4);/**/
}

Utility_Node Four_of_a_Kind_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int Number_of_the_Place=0,Value_place_First=0,Value_place_Second=0;
	
	int Four_of_a_Kind_First=Spade&Heart&Diamond&Club,Four_of_a_Kind_Second=Spade|Heart|Diamond|Club;
	
	while(Four_of_a_Kind_First)
	{
		Number_of_the_Place++;
		if(Four_of_a_Kind_First%2) Value_place_First=Number_of_the_Place;
		Four_of_a_Kind_First/=2;
	}
	
	Number_of_the_Place=0;
	
	while(Four_of_a_Kind_Second)
	{
		Number_of_the_Place++;
		if(Four_of_a_Kind_Second%2 && Number_of_the_Place!=Value_place_First) Value_place_Second=Number_of_the_Place;
		Four_of_a_Kind_Second/=2;
	}
	
	if(Value_place_First&&Value_place_Second) return Utility_Node(8,Value_place_First,Value_place_First,Value_place_First,Value_place_First,Value_place_Second);
	else return Utility_Node(0,0,0,0,0,0);
}

Utility_Node Full_House_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int Full_House_First=((Spade|Heart)&(Diamond|Club))&((Spade&Heart)|(Diamond&Club));
	int Full_House_Second=((Spade|Heart)&(Diamond|Club))|((Spade&Heart)|(Diamond&Club));
	
	int Number_of_the_Place=0,Value_place_First=0,Value_place_Second=0;
	
	while(Full_House_First)
	{
		Number_of_the_Place++;
		if(Full_House_First%2==1) Value_place_First=Number_of_the_Place;
		Full_House_First/=2;
	}
	
	Number_of_the_Place=0;
	
	while(Full_House_Second)
	{
		Number_of_the_Place++;
		if(Full_House_Second%2==1 && Number_of_the_Place!=Value_place_First) Value_place_Second=Number_of_the_Place;
		Full_House_Second/=2;
	}
	
	if(Value_place_First&&Value_place_Second) return Utility_Node(7,Value_place_First,Value_place_First,Value_place_First,Value_place_Second,Value_place_Second);
	else return Utility_Node(0,0,0,0,0,0);
}

Utility_Node Flush_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	Utility_Node Spade_Flush=Flush_Verification_Secondary_Single_Color_Verification(Spade);
	Utility_Node Heart_Flush=Flush_Verification_Secondary_Single_Color_Verification(Heart);
	Utility_Node Diamond_Flush=Flush_Verification_Secondary_Single_Color_Verification(Diamond);
	Utility_Node Club_Flush=Flush_Verification_Secondary_Single_Color_Verification(Club);
	
	Utility_Node Flush=max(max(Spade_Flush,Heart_Flush),max(Diamond_Flush,Club_Flush));
	
	Utility_Node Flush_Correction=Utility_Node(Flush.Type,Flush.Value_1,Flush.Value_2,Flush.Value_3,Flush.Value_4,Flush.Value_5);
	
	return Flush_Correction;
}

Utility_Node Straight_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	int Total=Spade|Heart|Diamond|Club;
	
	int Total_Straight=max(Total&(Total<<1)&(Total<<2)&(Total<<3)&(Total<<4),Total&(Total<<1)&(Total<<2)&(Total<<3)&(Total>>9));

	int Value_1=0/**/;
	
	while(Total_Straight)/**/
	{
		Value_1++;
		Total_Straight=Total_Straight>>1;
	}
	
	if(!Value_1) return Utility_Node(0,0,0,0,0,0);
	
	if(Value_1==4) return Utility_Node(5,4,3,2,1,13);
	else return Utility_Node(5,Value_1,Value_1-1,Value_1-2,Value_1-3,Value_1-4);/**/
}

Utility_Node Three_of_a_Kind_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int Three_of_a_Kind_First=((Spade|Heart)&(Diamond|Club))&((Spade&Heart)|(Diamond&Club));
	int Three_of_a_Kind_Second=Spade|Heart|Diamond|Club;
	
	int Number_of_the_Place=0,Value_place_First=0,Value_place_Second=0,Value_place_Third=0;
	
	while(Three_of_a_Kind_First)
	{
		Number_of_the_Place++;
		if(Three_of_a_Kind_First%2==1) Value_place_First=Number_of_the_Place;
		Three_of_a_Kind_First/=2;
	}
	
	Number_of_the_Place=0;
	
	while(Three_of_a_Kind_Second)
	{
		Number_of_the_Place++;
		if(Three_of_a_Kind_Second%2==1 && Number_of_the_Place!=Value_place_First) 
		{
			Value_place_Third=Value_place_Second;
			Value_place_Second=Number_of_the_Place;
		}
		Three_of_a_Kind_Second/=2;
	}
	
	if(Value_place_First&&Value_place_Second&&Value_place_Third) return Utility_Node(4,Value_place_First,Value_place_First,Value_place_First,Value_place_Second,Value_place_Third);
	else return Utility_Node(0,0,0,0,0,0);
}

Utility_Node Two_Pairs_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int Two_Pairs_First=((Spade|Heart)&(Diamond|Club))|((Spade&Heart)|(Diamond&Club));
	int Two_Pairs_Second=Spade|Heart|Diamond|Club;
	
	int Number_of_the_Place=0,Value_place_First=0,Value_place_Second=0,Value_place_Third=0;
	
	while(Two_Pairs_First)
	{
		Number_of_the_Place++;
		if(Two_Pairs_First%2==1) 
		{
			Value_place_Second=Value_place_First;
			Value_place_First=Number_of_the_Place;
		}
		Two_Pairs_First/=2;
	}
	
	Number_of_the_Place=0;
	
	while(Two_Pairs_Second)
	{
		Number_of_the_Place++;
		if(Two_Pairs_Second%2==1 && Number_of_the_Place!=Value_place_First && Number_of_the_Place!=Value_place_Second) Value_place_Third=Number_of_the_Place;
		Two_Pairs_Second/=2;
	}
	
	if(Value_place_First&&Value_place_Second&&Value_place_Third) return Utility_Node(3,Value_place_First,Value_place_First,Value_place_Second,Value_place_Second,Value_place_Third);
	else return Utility_Node(0,0,0,0,0,0);
}

Utility_Node One_Pair_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int One_Pair_First=((Spade|Heart)&(Diamond|Club))|((Spade&Heart)|(Diamond&Club));
	int One_Pair_Second=Spade|Heart|Diamond|Club;
	
	int Number_of_the_Place=0,Value_place_First=0,Value_place_Second=0,Value_place_Third=0,Value_place_Fourth=0,Number_of_the_State=0,Value_place[10];
	
	while(One_Pair_First)
	{
		Number_of_the_Place++;
		if(One_Pair_First%2==1) Value_place_First=Number_of_the_Place;
		One_Pair_First/=2;
	}
	
	Number_of_the_Place=0;
	
	while(One_Pair_Second)
	{
		Number_of_the_Place++;
		if(One_Pair_Second%2 && Number_of_the_Place!=Value_place_First)
		{
			Number_of_the_State++;
			Value_place[Number_of_the_State]=Number_of_the_Place;
		}
		One_Pair_Second/=2;
	}
	
	if(Value_place_First!=0 && Number_of_the_State>=3) return Utility_Node(2,Value_place_First,Value_place_First,Value_place[Number_of_the_State],Value_place[Number_of_the_State-1],Value_place[Number_of_the_State-2]);
	else return Utility_Node(0,0,0,0,0,0);
}

Utility_Node High_Card_Verification(State_Node State)
{
	int Spade=State.Spade;/**/
	int Heart=State.Heart;
	int Diamond=State.Diamond;
	int Club=State.Club;
	
	int High_Card=Spade|Heart|Diamond|Club;
	
	Utility_Node High_Card_Correction=High_Card_Secondary_Verification(High_Card);
	
	return High_Card_Correction;
}



Utility_Node Flush_Verification_Secondary_Single_Color_Verification(int Single_State)
{
	int Number_of_the_State=0,Number_of_the_Place=0,Value_place[10];
	
	while(Single_State)
	{
		Number_of_the_Place++;
		if(Single_State%2)
		{
			Number_of_the_State++;
			Value_place[Number_of_the_State]=Number_of_the_Place;
		}
		Single_State/=2;
	}
	
	if(Number_of_the_State>=5) return Utility_Node(6,Value_place[Number_of_the_State],Value_place[Number_of_the_State-1],Value_place[Number_of_the_State-2],Value_place[Number_of_the_State-3],Value_place[Number_of_the_State-4]);
	else return Utility_Node(0,0,0,0,0,0);
}

Utility_Node High_Card_Secondary_Verification(int Single_State)
{
	int Number_of_the_State=0,Number_of_the_Place=0,Value_place[10];
	
	while(Single_State)
	{
		Number_of_the_Place++;
		if(Single_State%2)
		{
			Number_of_the_State++;
			
			Value_place[Number_of_the_State]=Number_of_the_Place;
		}
		Single_State/=2;
	}
	
	if(Number_of_the_State>=5) return Utility_Node(1,Value_place[Number_of_the_State],Value_place[Number_of_the_State-1],Value_place[Number_of_the_State-2],Value_place[Number_of_the_State-3],Value_place[Number_of_the_State-4]);
	else return Utility_Node(0,0,0,0,0,0);
}

int main()
{
	srand((unsigned)time(NULL)); 
	
	int Player_1=0,Player_2=0,Hands=0;
	
	while(1)
	{
		Outcome_Node Outcome=Game_Structure();
		
		if(Outcome.Player==1) Player_1+=Outcome.Value;
		else Player_2+=Outcome.Value;
		
		cout<<"Winner: "<<Outcome.Player<<endl;
		cout<<"Value: "<<Outcome.Value<<endl;
		
		cout<<endl;
		
		cout<<"Player 1 Total Value: "<<Player_1-Player_2<<endl;
		cout<<"Player 2 Total Value: "<<Player_2-Player_1<<endl<<endl<<endl<<endl;		
	} 
//
//	
//	while(Hands)
//	{
//		Hands++;
//		
//		if(Hands%2==1)
//		{
//			Outcome_Node Outcome=Game_Structure();
//			
//			if(Outcome.Player==1) Player_1+=Outcome.Value;
//			else Player_2+=Outcome.Value;
//			
//			cout<<"Winner: "<<Outcome.Player<<endl;
//			cout<<"Value: "<<Outcome.Value<<endl;
//			
//			cout<<endl;
//			
//			cout<<"Player 1 Total Value: "<<Player_1-Player_2<<endl;
//			cout<<"Player 2 Total Value: "<<Player_2-Player_1<<endl<<endl<<endl<<endl;
//		}
//		else
//		{
//			Outcome_Node Outcome=Game_Structure();
//			
//			if(Outcome.Player==1) Player_1+=Outcome.Value;
//			else Player_2+=Outcome.Value;
//			
//			cout<<"Winner: "<<Outcome.Player<<endl;
//			cout<<"Value: "<<Outcome.Value<<endl;
//			
//			cout<<endl;
//			
//			cout<<"Player 1 Total Value: "<<Player_1-Player_2<<endl;
//			cout<<"Player 2 Total Value: "<<Player_2-Player_1<<endl<<endl<<endl<<endl;
//		}
//
//	}
//	
//	while(1)
//	{
//		State_Node State=Initiate();
//		Utility_Node Utility_Value=Utility(State);
//		Output(Utility_Value); 	
//		//if(!Self_Checking_System(Utility_Value)) break;//this function is for testing whether the program is correct or not
//	} 

	return 0;
}

