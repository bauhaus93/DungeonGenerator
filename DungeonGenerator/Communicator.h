#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>

#include "Tile.h"

#ifdef PIPE_NAME
#error "PIPE_NAME is already existing!"
#endif

#define BUFFER_SIZE 4096
#define TIMEOUT 10000
#define PIPE_NAME "\\\\.\\pipe\\MWSEDungeonCreator"

class Communicator{

private:
	HANDLE		hPipe;
	char		buffer[BUFFER_SIZE];
	DWORD		writeBufferSize;
	bool		connected;
	bool		error;

	void		Read();
	void		Write();

	void		Error(std::string function);

public:
				Communicator();
				~Communicator();
	bool		HasError();
	bool		Connect();
	bool		Connected();
	void		Disconnect();
	std::string	ReadString();
	float		ReadFloat();
	short		ReadShort();
	long		ReadLong();

	void		WriteTile(const Tile & tile);
};

