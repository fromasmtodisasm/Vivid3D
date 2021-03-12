#pragma once
#include "pch.h"
#include <stdio.h>
#include "strings.h"
#include <string>
const char* strAddInt(const char *s, int num)
{
	
	int ol = 1;


for (int i = 0; i < 2000; i++) {

	if (s[i] == "\0"[0])
	{
		break;
	}

	ol++;
}

char integer_string[32];
int integer = num;

char* ns = (char*)malloc(300);

for (int i = 0; i < 300; i++) {

	if (s[i] == "\0"[0])
	{
		ns[i] = "\0"[0];
		break;
	}
	ns[i] = s[i];

}

sprintf(integer_string, "%d", integer);

strcat(ns, integer_string);

return ns;

//	char* newS = (char*)malloc(ol+30);


	//std::ostringstream s2;
	//str << s << num;




}


bool strSame(const char* s1, const char* s2) {

	printf("S1:");

	printf(s1);
	printf("\n");
	printf("S2:");
	printf(s2);
	printf("\n");

	for (int i = 0; i < 255; i++) {
		if (s1[i] == "\0"[0])
		{
			if (s2[i] == "\0"[0]) {
				return true;
			}
			else {
				return false;
			}
		}
		if (!(s1[i] == s2[i]))
		{
			return false;
		}

	}
	return true;

}

const char * KeyToChar(int key,int mod) {

	if (mod == 0) {
		switch (key) {
		case GLFW_KEY_MINUS:
			return "-";
		case GLFW_KEY_EQUAL:
			return "=";
			
		case GLFW_KEY_PERIOD:
			return ".";
		case GLFW_KEY_COMMA:
			return ",";
		case GLFW_KEY_SLASH:
		case GLFW_KEY_BACKSLASH:
			return "/";
		case GLFW_KEY_A:
			return "a";
		case GLFW_KEY_B:
			return "b";
		case GLFW_KEY_C:
			return "c";
		case GLFW_KEY_D:
			return "d";
		case GLFW_KEY_E:
			return "e";
		case GLFW_KEY_F:
			return "f";
		case GLFW_KEY_G:
			return "g";
		case GLFW_KEY_H:
			return "h";
		case GLFW_KEY_I:
			return "i";
		case GLFW_KEY_J:
			return "j";
		case GLFW_KEY_K:
			return "k";
		case GLFW_KEY_L:
			return "l";
		case GLFW_KEY_M:
			return "m";
		case GLFW_KEY_N:
			return "n";
		case GLFW_KEY_O:
			return "o";
		case GLFW_KEY_P:
			return "p";
		case GLFW_KEY_Q:
			return "q";
		case GLFW_KEY_R:
			return "r";
		case GLFW_KEY_S:
			return "s";
		case GLFW_KEY_T:
			return "t";
		case GLFW_KEY_U:
			return "u";
		case GLFW_KEY_V:
			return "v";
		case GLFW_KEY_W:
			return "w";
		case GLFW_KEY_X:
			return "x";
		case GLFW_KEY_Y:
			return "y";
		case GLFW_KEY_Z:
			return "z";
		case GLFW_KEY_0:
			return "0";
		case GLFW_KEY_1:
			return "1";
		case GLFW_KEY_2:
			return "2";
		case GLFW_KEY_3:
			return "3";
		case GLFW_KEY_4:
			return "4";
		case GLFW_KEY_5:
			return "5";
		case GLFW_KEY_6:
			return "6";
		case GLFW_KEY_7:
			return "7";
		case GLFW_KEY_8:
			return "8";
		case GLFW_KEY_9:
			return "9";
		case GLFW_KEY_SPACE:
			return " ";
		}
	}
	else {
		switch (key) {
		case GLFW_KEY_MINUS:
			return "_";
		case GLFW_KEY_EQUAL:
				return "+";
		case GLFW_KEY_SLASH:
		case GLFW_KEY_BACKSLASH:
			return "?";
		case GLFW_KEY_PERIOD:
			return ">";
		case GLFW_KEY_COMMA:
			return "<";
		case GLFW_KEY_A:
			return "A";
		case GLFW_KEY_B:
			return "B";
		case GLFW_KEY_C:
			return "C";
		case GLFW_KEY_D:
			return "D";
		case GLFW_KEY_E:
			return "E";
		case GLFW_KEY_F:
			return "F";
		case GLFW_KEY_G:
			return "G";
		case GLFW_KEY_H:
			return "H";
		case GLFW_KEY_I:
			return "I";
		case GLFW_KEY_J:
			return "J";
		case GLFW_KEY_K:
			return "K";
		case GLFW_KEY_L:
			return "L";
		case GLFW_KEY_M:
			return "M";
		case GLFW_KEY_N:
			return "N";
		case GLFW_KEY_O:
			return "O";
		case GLFW_KEY_P:
			return "P";
		case GLFW_KEY_Q:
			return "Q";
		case GLFW_KEY_R:
			return "R";
		case GLFW_KEY_S:
			return "S";
		case GLFW_KEY_T:
			return "T";
		case GLFW_KEY_U:
			return "U";
		case GLFW_KEY_V:
			return "V";
		case GLFW_KEY_W:
			return "W";
		case GLFW_KEY_X:
			return "X";
		case GLFW_KEY_Y:
			return "Y";
		case GLFW_KEY_Z:
			return "Z";
		case GLFW_KEY_0:
			return ")";
		case GLFW_KEY_1:
			return "!";
		case GLFW_KEY_2:
			return "@";
		case GLFW_KEY_3:
			return "#";
		case GLFW_KEY_4:
			return "$";
		case GLFW_KEY_5:
			return "%";
		case GLFW_KEY_6:
			return "^";
		case GLFW_KEY_7:
			return "&";
		case GLFW_KEY_8:
			return "*";
		case GLFW_KEY_9:
			return "(";
		case GLFW_KEY_SPACE:
			return " ";
		}
	}
	

}