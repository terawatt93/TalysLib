/// \file
/// \ingroup tutorial_net
/// This script shows how to make a simple iterative server that
/// can accept connections while handling currently open connections.
/// Compare this script to hserv.C that blocks on accept.
/// In this script a server socket is created and added to a monitor.
/// A monitor object is used to monitor connection requests on
/// the server socket. After accepting the connection
/// the new socket is added to the monitor and immediately ready
/// for use. Once two connections are accepted the server socket
/// is removed from the monitor and closed. The monitor continues
/// monitoring the sockets.
///
/// To run this demo do the following:
///   - Open three windows
///   - Start ROOT in all three windows
///   - Execute in the first window: .x hserv2.C
///   - Execute in the second and third windows: .x hclient.C
///
/// \macro_code
///
/// \author Fons Rademakers
#include <TalysLib.hh>
#include <Parser.cpp>
void TestServer()
{
	TServerSocket *ss = new TServerSocket(9090, kTRUE);
	TMonitor *mon = new TMonitor;
	mon->Add(ss);
	TSocket *s0 = 0;
	while (1) 
	{
		TMessage *mess;
		TSocket  *s;
		s = mon->Select();
		if (s->IsA() == TServerSocket::Class()) 
		{
			if (!s0)
			{
				s0 = ((TServerSocket *)s)->Accept();
				s0->Send("go 0");
				mon->Add(s0);
			}
			if (s0)
			{
				mon->Remove(ss);
				//ss->Close();
			}
			continue;
		}
		s->Recv(mess);
		if(mess)
		{
			if (mess->What() == kMESS_STRING) 
			{
				char str[1000];
				mess->ReadString(&str[0], 1000);
				stringstream sstr(str);
				cout<<str<<"\n";
				string command, argument;
				sstr>>command>>argument;
				if(command=="create")
				{
					int Z,A;
					GetAZ(argument,Z,A);
					if((A>0)||(Z>0))
					{
						Nucleus Nucl(argument);
						//Nucl.GenerateProducts();
						TMessage m(kMESS_OBJECT);
						m.WriteObject(&Nucl);
						s0->Send(m);
					}
					mon->Remove(s);
				}
			}
			else if (mess->What() == kMESS_OBJECT) 
			{
				//printf("got object of class: %s\n", mess->GetClass()->GetName());
				TObject *PointerToObject=mess->ReadObject(mess->GetClass());
				if(PointerToObject->InheritsFrom("Nucleus"))
				{
					Nucleus *Nucl=(Nucleus*)PointerToObject;
					Nucl->AssignPointers();
					Nucl->GenerateProducts();
					
					TMessage m(kMESS_OBJECT);
					m.WriteObject(Nucl);
					s0->Send(m);
					mon->Remove(s);
				}
				
			}
			if (mon->GetActive() == 0) 
			{
				printf("No more active clients... stopping\n");
				printf("Client 0: bytes recv = %d, bytes sent = %d\n", s0->GetBytesRecv(),s0->GetBytesSent());
				s0->Close();
				s0=0;
				if(!s0)
				{
					cout<<"s closed\n";
				}
			//ss = new TServerSocket(9090, kTRUE);
				mon->Add(ss);
			//break;
			}
		}
		
		//delete mess;
	}
}
