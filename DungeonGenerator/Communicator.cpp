#include "Communicator.h"

using namespace std;

Communicator::Communicator():
	connected{false}{
	hPipe = CreateNamedPipe(	PIPE_NAME,
								PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
								BUFFER_SIZE,
								BUFFER_SIZE,
								TIMEOUT,
								NULL);

	
	if (hPipe == INVALID_HANDLE_VALUE)
		Error("CreateNamedPipe");
	else
		cout << "Created named pipe " << PIPE_NAME << endl;
} 

Communicator::~Communicator(){
	CloseHandle(hPipe);
}

bool Communicator::HasError(){
	return error;
}

bool Communicator::Connect(){
	if (!ConnectNamedPipe(hPipe, NULL)){
		Error("ConnectNamedPipe");
		connected = false;
		return false;
	}
	connected = true;
	cout << "Communicator connected!" << endl;
	return true;
}

bool Communicator::Connected(){
	return connected;
}

void Communicator::Disconnect(){
	DisconnectNamedPipe(hPipe);
	connected = false;
	cout << "Communicator disconnected!" << endl;
}

void Communicator::Read(){
	DWORD size = 0;

	memset(buffer, 0, sizeof buffer);

	if (HasError())
		return;
	
	if (ReadFile(hPipe, buffer, BUFFER_SIZE, &size, NULL)){
		buffer[size] = 0;
	}
	else{
		memset(buffer, 0, sizeof buffer);
		error = true;
		Error("ReadFile");
	}
}

string Communicator::ReadString(){
	Read();
	return string(buffer);
}

float Communicator::ReadFloat(){
	Read();
	return *((float*)buffer);
}

short Communicator::ReadShort(){
	Read();
	return *((short*)buffer);
}

long Communicator::ReadLong(){
	Read();
	return *((long*)buffer);
}

void Communicator::Write(){
	DWORD written = -1;

	if (HasError())
		return;

	if (WriteFile(hPipe, buffer, writeBufferSize, &written, NULL)){
		if (written != writeBufferSize)
			cout << "Incomplete write: " << written << "/" << writeBufferSize << endl;
	}
	else{
		error = true;
		Error("WriteFile");
	}
}

void Communicator::WriteTile(const Tile& tile){
	memset(buffer, 0, sizeof buffer);
	snprintf(buffer, BUFFER_SIZE, "%f %f %f %f %s\n", tile.GetPos().GetX(), tile.GetPos().GetY(), tile.GetPos().GetZ(), tile.GetZRot(), tile.GetID().c_str());
	cout << "sending: " << buffer;
	writeBufferSize = strlen(buffer);
	Write();
}

void Communicator::Error(string function){
	cerr << "[ERROR] " << function;
	if (GetLastError() != 0){
		cerr << ": GetLastError = " << GetLastError();
	}
	cerr << endl;
}

