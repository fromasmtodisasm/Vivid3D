#pragma once
class VString
{
public:
	VString(const char* text);
	VString();
	VString(float v);
	VString(int v);
	int Len();
	void Add(VString s);
	char GetChar(int n);
	bool IsSame(VString b) {

		for (int i = 0; i < 2555; i++) {

			if (data[i] != b.GetConst()[i])
			{
				return false;
			}

			if (data[i] == "\0"[0] && b.GetConst()[i] == "\0"[0])
			{
				return true;
			}

		}
		return false;
	}


	void Replace(char c, char w);

	const char* GetConst() {

		return (const char*)data;

	}

	int Find(const char* f, int sc = 0);

	VString SubString(int i, int l);
	//void AddInt(int num);
	float ToFloat();
	int ToInt();
	double ToDouble();
private:
	char* data;
};

