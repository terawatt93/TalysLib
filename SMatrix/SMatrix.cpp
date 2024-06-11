#include "SMatrix.hh"

// calclation of Racah function U(j1,j2,j5,j4;j3,j6)

double Racah(double j1, double j2, double j5, double j4, double j3, double j6)// j1,j2,j4,j5 ; j3,j6
{
	int twoj1 = int(2*j1), twoj2 = int(2*j2), twoj3 = int(2*j3), 
		twoj4 = int(2*j4), twoj5 = int(2*j5), twoj6 = int(2*j6); 
	//cout<<"racah two "<<twoj1<<" "<<twoj2<<" "<<twoj3<<" "<<twoj4<<" "<<twoj5<<" "<<twoj6<<endl; 
	//cout<<"POWER "<< pow(-1,j1+j2+j4+j5)<<endl;
	//cout<<"6j "<<wigner_6j(twoj1, twoj2, twoj3, twoj4, twoj5, twoj6)<<endl;
	return pow(-1,j1+j2+j4+j5)*sqrt((2*j3+1)*(2*j6+1))
			*wigner_6j(twoj1, twoj2, twoj3, twoj4, twoj5, twoj6);
}


// calculation of clebsh_gordan coefficients C_{j1 m1 j2 m2}^{j3 m3}

double clebsh_gordan(double j1,double m1, double j2,double m2, double j3, double m3)
{
	int twoj1 = int(2*j1), twoj2 = int(2*j2), twoj3 = int(2*j3), 
		twom1 = int(2*m1), twom2 = int(2*m2), twom3 = int(2*m3); 
	//cout<<"wigner "<<wigner_3j(twoj1,twoj2,twoj3,twom1,twom2,-twom3)<<endl;
	return pow(-1,-j1+j2-m3)*sqrt(2*j3+1)*wigner_3j(twoj1,twoj2,twoj3,twom1,twom2,-twom3); 
	
}

// calculation of 9j-symbols 
//  ( j1 j2 j3 )
//  ( j4 j5 j6 )
//  ( j7 j8 j9 )

double j9sym(double j1, double j2, double j3, double j4, double j5, double j6, double j7, double j8, double j9)
{
	int twoj1 = int(2*j1), twoj2 = int(2*j2), twoj3 = int(2*j3), 
		twoj4 = int(2*j4), twoj5 = int(2*j5), twoj6 = int(2*j6),
		twoj7 = int(2*j7), twoj8 = int(2*j8), twoj9 = int(2*j9); 
	return wigner_9j(twoj1, twoj2, twoj3, twoj4, twoj5, twoj6, twoj7, twoj8, twoj9);
}

double g_J(double J, double s, int Ia)
{	
	return (2*J+1)/((2*s+1)*(2*Ia+1));
}

// make vector of allowed transmission from alpha channel to beta channel (related to spin  and paritty conservation)

vector<tuple<double, int, double, int, double>> lj() {
  double s = 1. / 2;
  int I_f = 0;
  int I_i = 2;
  int L = 2;
  double I_a = 0;
  vector<tuple<double, int, double, int, double>> a;
  for (int l_alpha = 0; l_alpha < 6; l_alpha++) {
    for (int l_beta = 0; l_beta < 6; l_beta++) {
      if (pow(-1, l_alpha + l_beta) == -1) {
        continue;
      }
      for (double j_alpha = abs(l_alpha - s); j_alpha < l_alpha + s + 1; j_alpha++) {
        for (double j_beta = abs(l_beta - s); j_beta < l_beta + s + 1; j_beta++) {
          double J = j_alpha;
          if ((J < abs(I_i - j_beta)) || (J > (I_i + j_beta))) {
            continue;
          }
          //cout<<"J "<< J<< " l_alpha "<< l_alpha<< " j_alpha "<< j_alpha<< " l_beta "<<l_beta<<" j_beta "<<j_beta<<endl;
          a.push_back(make_tuple(J, l_alpha, j_alpha, l_beta, j_beta));
        }
      }
    }
  }
 
  return a;
}


// class of coefficients before angular functuons 
// D^{lam}_{lam1 Q}

Dlam::Dlam(int Lam,int Lam1,int QQ)
{
	lam=Lam, lam1=Lam1, Q=QQ;

	double c1 = clebsh_gordan(L,1,Q,0,L,1); 
	
	double raca = Racah(If,Ii,L,Q,L,Ii); 
	double coef = sqrt(2*Q+1)*sqrt((2*Ii+1)*(2*lam1+1));
	beg = raca*coef*c1;
}

int Dlam::addS(ST_Matrix &AD)
{
	double c1 = 0, c2 = 0, racah1 = 0, racah2 = 0, racah3 = 0, j9 = 0, coef = 0;
	int la, la1, lb, lb1;
	double J,J1, ja,ja1,jb,jb1;	
	complexd summa = complexd(0,0);
	BlockNumber=AD.BlockNumber;
	for (auto &a : lj()) 
	{
		for(auto &a1 : lj()) 
		{
			//cout<<get<1>(a1)<<endl;
			//tuple aa = a;
			//tuple aa1 = a1;
			J = get<0>(a);
			la = get<1>(a);
			ja = get<2>(a);
			lb = get<3>(a);
			jb = get<4>(a); 
			J1 = get<0>(a1);;
			la1 = get<1>(a1);
			ja1 = get<2>(a1);
			lb1 = get<3>(a1);
			jb1 = get<4>(a1);
			
			//cout<<"J "<<J<<" la "<<la<<" ja "<<ja<<" lb "<<lb<<" jb "<<jb<<endl;
			//cout<<"J1 "<<J1<<" la1 "<<la1<<" ja1 "<<ja1<<" lb1 "<<lb1<<" jb1 "<<jb1<<endl;
			coef = g_J(J1)* sqrt((2*J+1)*(2*jb1+1));
			
			c1 = clebsh_gordan(la1,0,lam,0,la,0);
			c2 = clebsh_gordan(lb1,0,lam1,0,lb,0);
			racah1 = Racah(s,ja1,la,lam,la1,ja);
			racah2 = Racah(Ia,J1,ja,lam,ja1,J);
			racah3 = Racah(s,jb1,lb,lam1,lb1,jb);
			j9 = j9sym(J,jb,Ii,J1,jb1,Ii,lam,lam1,Q);
			//cout<<"clebsh "<<c1<< " c "<<c2<<endl;
			//cout<<racah1<<" r "<<racah2<<" r "<<racah3<<" r "<<j9<<endl;
			coef *= c1*c2*racah1*racah2*racah3*j9;
			if(coef==0) continue;
			//complexd S = AD.S1[make_tuple(2,0,la,lb,ja,jb)]*conj(AD.S1[make_tuple(2,0,la1,lb1,ja1,jb1)]);//el = 2 - inelastic, nb = 0 - the first block
			complexd S = AD.S1[make_tuple(2,BlockNumber,la,lb,ja,jb)]*conj(AD.S1[make_tuple(2,BlockNumber,la1,lb1,ja1,jb1)]);//el = 2 - inelastic, nb = 0 - the first block//cout<<"SMTuple:"<<2<<" "<<0<<" "<<la<<" "<<lb<<" "<<ja<<" "<<jb<<"\n";
			//cout<<"SM="<<AD.S1[make_tuple(2,0,la,lb,ja,jb)]<<endl;
			//cout<<coef<<endl;
			summa += S*coef;
			//cout<<summa<<endl;
		}
	
	}
	result += beg*summa;
	
	return 2;
}

int Dlam::addT(ST_Matrix &AD)
{
	double c1 = 0, c2 = 0, racah1 = 0, racah2 = 0, racah3 = 0, j9 = 0, coef = 0;
	int la, la1, lb, lb1;
	double J,J1, ja,ja1,jb,jb1;	
	TString parity;
	complexd summa = complexd(0,0);
	for (auto &a : lj()) 
	{

			//cout<<get<1>(a1)<<endl;
			//tuple aa = a;
			//tuple aa1 = a1;
		J = get<0>(a);
		la = get<1>(a);
		ja = get<2>(a);
		lb = get<3>(a);
		jb = get<4>(a); 
		
		if(la%2 == 0) parity = "+";
        else if (la%2 == 1) parity = "-";
			
		//cout<<"J "<<J<<" la "<<la<<" ja "<<ja<<" lb "<<lb<<" jb "<<jb<<endl;
		
		coef = g_J(J)* sqrt((2*J+1)*(2*jb+1));
		//cout<<"before "<<coef<<endl;
		c1 = clebsh_gordan(la,0,lam,0,la,0);
		c2 = clebsh_gordan(lb,0,lam1,0,lb,0);
		racah1 = Racah(s,ja,la,lam,la,ja);
		racah2 = Racah(Ia,J,ja,lam,ja,J);
		racah3 = Racah(s,jb,lb,lam1,lb,jb);
		j9 = j9sym(J,jb,Ii,J,jb,Ii,lam,lam1,Q);
		//cout<<"clebsh "<<c1<< " c "<<c2<<endl;
		//cout<<racah1<<" r "<<racah2<<" r "<<racah3<<" r "<<j9<<endl;
		coef *= c1*c2*racah1*racah2*racah3*j9;
		//cout<<beg*coef<<endl;
		if(coef==0) continue;
		
		double T = AD.Trans[make_tuple("neutron",0,la,ja,J,parity)]
                       *AD.Trans[make_tuple("neutron",1,lb,jb,J,parity)]/AD.Tfull[make_tuple(J,parity)];
        //cout<<"trans "<<T<<endl;
		summa += T*coef;
		//cout<<summa<<endl;
	}
	result +=beg*summa;
	//cout<<result<<endl;
	
	return 2;
}

int ST_Matrix::ReadSmatrix(string SMBuf)
{
  stringstream f(SMBuf);
  string line;
  vector<string> lines;
  if(SMBuf.size()>0)
  {
	  WasRead=true;
  }
  while (getline(f, line)) {
    lines.push_back(line);
  }

  // read from lines to dict S1[(level,nb,l_a,l_b,j_a,j_b)] level - elastic, non-elastic,
  // nb - number of block (depends on nucleus state)
  int nl = 0, nb = 0;

  while (nl != int(lines.size())) {
    string line1 = lines[nl];
    nl++;
    istringstream iss1(line1);
    string m_n, E, m_C12, nlines, s_mat,zero;
    iss1 >> s_mat >>m_n >> E >> m_C12 >>zero >> nlines;
    int nlinesInt = stoi(nlines);
    
    for (int i = 0; i < nlinesInt; i++) {
      string line2 = lines[nl];
      nl++;
      istringstream iss2(line2);
      double j_a;
      TString p;
      int count;
      iss2 >> j_a >> p >> count;

      int l_a = j_a/1;
      if (p == "+") {
        if (l_a % 2 != 0) {
          l_a++;
        }
      } else if (p == "-") {
        if (l_a % 2 == 0) {
          l_a++;
        }
      }
      for (int j = 0; j < count; j++) {
        string line3 = lines[nl];
        nl++;
        istringstream iss3(line3);
        int el, l_b, zero1, zero2;
        double j_b;
        TString reS, imS, SS, im;
        
        
        iss3 >> zero1>>zero2>>el >> l_b >> j_b >> reS >> imS>>im>> SS;
       
        reS.ReplaceAll("D","e");
        imS.ReplaceAll("D","e");
        SS.ReplaceAll("D","e");
        complexd S = complexd(atof(reS), atof(imS));
        S1[make_tuple(el, nb, l_a, l_b, j_a, j_b)] = S;
       // cout<<"S1("<<el<<" "<<nb<<" "<<l_a<<" "<<l_b<<" "<<j_a<<" "<<j_b<<") "<<S<<"\n";
        Smod[make_tuple(el, nb, l_a, l_b, j_a, j_b)] = atof(SS);
      }
    }
    nb += 1;
  }

	return 1;
}

int ST_Matrix::ReadTransCoef(string TransBuf)
{
  stringstream f(TransBuf);
  string line;
  vector<string> lines;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  // read from lines to dict S1[(level,nb,l_a,l_b,j_a,j_b)] level - elastic, non-elastic,
  // nb - number of block (depends on nucleus state)
  int nl = 0;

  while (nl != int(lines.size())) {
    string line1 = lines[nl];
    nl++;
    istringstream iss1(line1);
    string tip;
    int level, spin, l;
    double T, E;
    int neut, prot, J1;
    TString parity;
    iss1 >> tip >> level >> spin >> l >> T >> E >> neut >> prot >> J1 >> parity;

    double j = spin / 2.0 + l;
    double J = J1 / 2.0;

    if (parity == "1") {
      parity = "+";
    } else if (parity == "-1") {
      parity = "-";
    }
   Trans[make_tuple(tip, level, l, j, J, parity)] = T;
   Tfull[make_tuple(J, parity)] = 0;
   // cout << make_tuple(tip, level, l, j, J, parity) << endl;
    //cout <<"tip "<<tip<<" level "<<level<<" spin "<<j<<" l "<<l<<" T "<<T<<" E "<<E<<" J1 "<<J<<" par "<<parity <<" Trans "<<T<< endl;
  }
	for (auto &i : Trans) {
		double J;
		TString parity;
      J = get<4>(i.first);
      parity = get<5>(i.first);

      Tfull[make_tuple(J, parity)] += i.second;

    }
  return 0;
}

// calculate D coefficients and gives two functuion TF1 for inelastic scattered neutron (1st level) and gamma distribution
/*void Dcoef_v2(TString inputname, TString outname)
{
	TString name1 = "./txt/"+outname+".txt";
	FILE *tf = fopen(name1,"w");
	ST_Matrix s_mat(inputname);
	map<tuple<int, int, int>, double> D; // write results of coefficients to map


	for (int Q = 0; Q < 6; Q += 2){
		for (int lam1 = 0; lam1 < 7; lam1++) {
			for (int lam = abs(Q - lam1); lam <= Q + lam1; lam++) {
			
				Dlam dl(lam, lam1, Q);
              
				dl.addS(s_mat);
				//dl.addT(s_mat);
				if (dl.pr_result() != 0) { 
				    D[make_tuple(lam, lam1, Q)] = dl.pr_result(); 
					cout<<"lam "<<lam<<" lam1 " <<lam1<<" Q "<<Q<<" result "<<D[(make_tuple(lam,lam1,Q))]<<endl;
					fprintf(tf,"%d %d %d %f %f\n",lam,lam1,Q, dl.pr_result(),dl.pr_result()*(2*lam+1));
				}
			}
		}
	}
	fclose(tf);
	TString neutron; 
	TString gamma;
	for(auto &i: D)
	{	auto j = i.first;
		int lam = get<0>(j),
			lam1 = get<1>(j),
			Q = get<2>(j);
		
		if(Q == 0)
		{
			if(i.second>0) neutron+="+";
			neutron+=TString::Format("%f*legendre(%d,cos(3.14*x/180))",i.second*(2*lam+1)/D[make_tuple(0,0,0)],lam);

		}
		if(lam1 == 0)
		{	
			if(i.second>0) gamma+="+";
			gamma+=TString::Format("%f*legendre(%d,cos(3.14*x/180))",i.second*(2*Q+1)/D[make_tuple(0,0,0)],Q);
		}
	}
	char c {'+'};
	neutron.Remove(TString::kLeading,c);
	gamma.Remove(TString::kLeading,c);
	cout<<gamma<<endl;
	cout<<"neutron "<<endl;
	cout<<neutron<<endl;

	TF1 *fgamma = new TF1("gamma",gamma,0,180);//угловое распределение гамма
	TF1 *fneutron = new TF1("neutron",neutron,0,180);//угловое распределение нейтронов

}*/
