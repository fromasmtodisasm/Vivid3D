#pragma once

template<class T>
class VNode {
public:
	T Data;
	VNode<T>* Next = NULL;
	VNode<T>* Prev = NULL;

};
template<class T>
class VList
{
public:
	VList()
	{
		First = NULL;
		Last = NULL;
	}
	VNode<T>* GetFirst()
	{
		return First;
	}
	VNode<T>* GetLast() {
		return Last;
	}

	void Add(T data) {

		VNode<T>* node = new VNode;
		node->Data = data;

		if (Last == NULL) {
			First = node;
			Last = node;
		}
		else {
			Last->Next = node;
			node->Prev = Last;
			Last = node;
		}

	}


private:
	VNode<T>* First;
	VNode<T>* Last;
};

