#pragma once
#include <sstream>
#include <iostream>
#include <TObject.h>

//! Variables for ECIS
//!   angbeg       ! first angle
//!   angend       ! last angle
//!   anginc       ! angle increment
//!   d2disp       ! constant for imaginary potential
//!   d3disp       ! constant for imaginary potential
//!   ecis1        ! 50 input flags ('T' or 'F') for ECIS
//!   ecis2        ! 50 input flags ('T' or 'F') for ECIS
//!   efer         ! Fermi energy
//!   Elevel       ! energy of level
//!   hint         ! integration step size h
//!   iband        ! band number of level
//!   idvib        ! identifier for existence of vibrational state inside rotational
//!   iph          ! help variable
//!   iqm          ! largest order of deformation
//!   iqmax        ! maximum l - value of multipole expansion
//!   iterm        ! number of iterations
//!   Jband        ! angular momentum
//!   Jlevel       ! spin of level
//!   Kmag         ! magnetic quantum number
//!   legendre     ! logical for output of Legendre coefficients
//!   Nband        ! number of vibrational bands
//!   ncoll        ! number of nuclear states
//!   njmax        ! maximal number of j - values in ECIS
//!   npp          ! number of optical potentials
//!   nrad         ! number of radial points
//!   Nrotbeta     ! number of deformation parameters for rotational nucleus
//!   rotbeta      ! deformation parameters for rotational nucleus
//!   Plevel       ! parity of level
//!   prodZ        ! product of charges of projectile and target nucleus
//!   projmass     ! mass of projectile
//!   resmass      ! mass of residual nucleus
//!   rmatch       ! matching radius
//!   spin         ! spin of incident particle
//!   tarparity    ! parity of target nucleus
//!   tarspin      ! spin of target nucleus
//!   title        ! title of ECIS input file
//!   vibbeta      ! vibrational deformation parameter
//!   w2disp       ! constant for imaginary potential
//! Variables for JLM
//!   normjlm      ! JLM potential normalization factors
//!   potjlm       ! JLM potential depth values
//!   radjlm       ! radial points for JLM potential
//! Variables for optical model
//!   av           ! real volume diffuseness
//!   avd          ! real surface diffuseness
//!   avso         ! real spin - orbit diffuseness
//!   aw           ! imaginary volume diffuseness
//!   awd          ! imaginary surface diffuseness
//!   awso         ! imaginary spin - orbit diffuseness
//!   disp         ! flag for dispersive optical model
//!   rc           ! Coulomb radius
//!   rv           ! real volume radius
//!   rvd          ! real surface radius
//!   rvso         ! real spin - orbit radius
//!   rw           ! imaginary volume radius
//!   rwd          ! imaginary surface radius
//!   rwso         ! imaginary spin - orbit radius
//!   v            ! real volume depth
//!   vd           ! real surface depth
//!   vso          ! real spin - orbit depth
//!   w            ! imaginary volume depth
//!   wd           ! imaginary surface depth
//!   wso          ! imaginary spin - orbit depth

class ECISinput//класс, обеспечивающий чтение файлов .inp для ECIS
{
	public:
	std::vector<bool> flags;
	string title;
	vector<bool> ecis1, ecis2;
	bool legendre=false, disp=false,vibrational=false;
	int ncoll, njmax, iterm, npp;
	double hint, rmatch;
	double w=0, rw=0, aw=0, vd=0, rvd=0, avd=0, wd=0, rwd=0, awd=0, vso=0, rvso=0, avso=0, wso=0, rwso=0, awso=0,rc=0,v=0,rv=0,av=0;
	double tarspin, e, spin, projmass, resmass, angbeg, anginc, angend, eopt,efer, w2disp,d3disp, d2disp;
	int tarparity, prodZ, idvib;
	vector<double> Jlevel, Elevel;
	vector<int> Plevel, iph,iband;
	static vector<ECISinput> ReadFromBuffer(string Buffer);
	static vector<ECISinput> ReadFromFile(string Filename);
};
