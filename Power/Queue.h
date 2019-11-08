#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue
{
public:
	Queue(){ head = null; tail = null; }
	~Queue(){ while (head != null){ Q_Node* temp = head; head = head->next; delete temp; }}

	void push(T data){
		Q_Node* newNode = new Q_Node(data);
		if (head == null){ head = newNode; tail = newNode; }
		else{ head->prev = newNode; newNode->next = head; head = newNode; }
		length++;
	}

	T pop() {
		if (head == null) { return null; }
		Q_Node* resNode = tail; tail = tail->prev;
		if (tail == null) { head = null; }
		else { tail->next = null; }
		length--;
		T result = resNode->Data;
		delete resNode;
		return result;
	}

	int getLength() const { return length; }

	bool isEmpty() const { return head == null; }

	struct Q_Node {
		T Data; Q_Node* next; Q_Node* prev;
		Q_Node(T data) { Data = data; next = null; prev = null; }
	};

private:
	Q_Node* head;
	Q_Node* tail;

	int length;
};

#endif