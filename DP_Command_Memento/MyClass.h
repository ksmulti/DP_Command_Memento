#pragma once
#include <stack>

enum 
{
	INNER_MSG_BATTLE = 0,
	INNER_MSG_SAVE,
	INNER_MSG_LOAD,
	INNER_MSG_UNDO,
	INNER_MSG_REST
};

class Command
{
public:
	virtual void execute() = 0;
	virtual void unexecute() = 0;
};

class Memento
{
	friend class Player;
public:
	Memento(const int& hp, const int& exp);
private:
	int hp;
	int exp;
};

class Caretaker
{
public:
	Caretaker();
	~Caretaker();
	Memento* GetMemento();
	void SetMemento(Memento* pMemento);
	Command* GetCommandFromStack();
	void SetCommandToStack(Command* pCommand);
	BOOL IsStackEmpty();
private:
	Memento* pMementoPlayer;
	std::stack<Command*> stackUndo;
};

class Observer
{
public:
	virtual void Update(UINT uMsg, LPVOID pParam = NULL) = 0;
};

class Subject
{
public:
	virtual void RegisterObserver(Observer *pObserver) = 0;
	virtual void RemoveObserver(Observer *pObserver) = 0;
	virtual void NotifyObservers(UINT uMsg, LPVOID pParam = NULL) = 0;
};

class Player : public Subject
{
public:
	Player();
	void Battle();
	void ReverseBattle();
	int GetHP();
	int GetEXP();
	Memento* SaveToMemento();
	void LoadFromMemento(Memento* pMemento);
	virtual void RegisterObserver(Observer* pObserver);
	virtual void RemoveObserver(Observer* pObserver);
	virtual void NotifyObservers(UINT uMsg, LPVOID pParam = NULL);
	void Rest();
	void ReverseRest();
private:
	int hp;
	int exp;
	CList<Observer*, Observer*> listObservers;
};

class BattleCommand : public Command
{
public:
	BattleCommand(Player* pPlayer, Caretaker* pCaretaker);
	virtual void execute();
	virtual void unexecute();
private:
	Player* pPlayer;
	Caretaker* pCaretaker;
};

class SaveCommand : public Command
{
public:
	SaveCommand(Player* pPlayer, Caretaker* pCaretaker);
	virtual void execute();
	virtual void unexecute();
private:
	Player* pPlayer;
	Caretaker* pCaretaker;
};

class LoadCommand : public Command
{
public:
	LoadCommand(Player* pPlayer, Caretaker* pCaretaker);
	virtual void execute();
	virtual void unexecute();
private:
	Player* pPlayer;
	Caretaker* pCaretaker;
};

class RestCommand : public Command
{
public:
	RestCommand(Player* pPlayer, Caretaker* pCaretaker);
	virtual void execute();
	virtual void unexecute();
private:
	Player* pPlayer;
	Caretaker* pCaretaker;
};

class UndoCommand : public Command
{
public:
	UndoCommand(Caretaker* pCaretaker);
	virtual void execute();
	virtual void unexecute();
private:
	Caretaker* pCaretaker;
};

