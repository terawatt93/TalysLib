Nucleus GetFromRemote(string name)
{
	TalysLibManager* m=TalysLibManager::GetPointer();
	TSocket *sock = new TSocket(m->RemoteIP.c_str(),m->RemotePort);
	char str[32];
	sock->Recv(str, 32);
	if(!(string(str).size()>0))
	{
		cout<<"Server "<<m->RemoteIP.c_str()<<":"<<m->RemotePort<<" does not responses!\n";
	}
	TMessage *mess;
	sock->Send(("create "+name).c_str());
	sock->Recv(mess);
	if (mess->What() == kMESS_OBJECT) 
	{
		//printf("got object of class: %s\n", mess->GetClass()->GetName());
		Nucleus *Nucl = (Nucleus*)mess->ReadObject(mess->GetClass());
		Nucl->AssignPointers();
		//Nucl->SaveToXLSX("remote.xlsx");
		delete mess;
		return *Nucl;
	}
}
