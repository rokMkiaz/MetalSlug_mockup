#pragma once


class Stage abstract
{
public:
	virtual   void    Start() abstract;
	virtual  Stage* Update()  abstract;
	virtual   void	    End() abstract;


	bool end = false;



};

