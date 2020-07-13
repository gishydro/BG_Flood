
#ifndef PARAM_H
#define PARAM_H

#include "General.h"
#include "input.h"

class Param {
public:
	//general parameters
	double g=9.81; // Gravity
	double rho=1025.0; // fluid density
	double eps= 0.0001; // //drying height in m
	double dt=0.0; // Model time step in s.
	double CFL=0.5; // Current Freidrich Limiter
	double theta=1.3; // minmod limiter can be used to tune the momentum dissipation (theta=1 gives minmod, the most dissipative limiter and theta = 2 gives	superbee, the least dissipative).
	int frictionmodel=0; // 
	double cf=0.0001; // bottom friction for flow model cf 
	double Cd=0.002; // Wind drag coeff
	double Pa2m = 0.00009916; // if unit is hPa then user should use 0.009916;
	double Paref = 101300.0; // if unit is hPa then user should use 1013.0 
	double lat = 0.0; // Model latitude. This is ignored in spherical case
	int GPUDEVICE=0; // 0: first available GPU; -1: CPU single core; 2+: other GPU

	int doubleprecision = 0;

	//grid parameters
	double dx= 0.0 / 0.0; // grid resolution in the coordinate system unit. 
	double delta; // grid resolution for the model. in Spherical coordinates this is dx * Radius*pi / 180.0
	int nx=0; // Initial grid size
	int ny=0; //Initial grid size
	int nblk=0; // number of compute blocks
	int blkwidth = 16;
	int blksize = 256; //16x16 blocks
	double xo = 0.0 / 0.0; // grid origin
	double yo = 0.0 / 0.0; // grid origin
	double ymax = 0.0 / 0.0;
	double xmax = 0.0 / 0.0;
	double grdalpha= 0.0 / 0.0; // grid rotation Y axis from the North input in degrees but later converted to rad
	int posdown = 0; // flag for bathy input. model requirement is positive up  so if posdown ==1 then zb=zb*-1.0f
	int spherical = 0; // flag for geographical coordinate. can be activated by using teh keyword geographic
	double Radius = 6371220.; //Earth radius [m]

	//Adaptation
	int initlevel = 0;
	int maxlevel = 0;
	int minlevel = 0;
	int nblkmem = 0;
	int navailblk = 0;
	double membuffer = 1.05; //needs to allocate more memory than initially needed so adaptation can happen without memory reallocation

	double mask = 9999.0; //mask any zb above this value. if the entire Block is masked then it is not allocated in the memory
	//files
	//std::string Bathymetryfile;// bathymetry file name
	inputmap Bathymetry;
	std::string outfile="Output.nc"; // netcdf output file name
	
	//Timekeeping
	double outputtimestep=0.0; //number of seconds between output 0.0 for none
	double endtime=0.0; // Total runtime in s will be calculated based on bnd input as min(length of the shortest time series, user defined)
	double totaltime = 0.0; //

	//Timeseries output
	std::vector<std::string> TSoutfile; //filename of output time series (Only save time, H U,V and zs)
	std::vector<TSnode> TSnodesout; // vector containing i and j of each variables
									//Output variables
	std::vector<std::string> outvars; //list of names of teh variables to output


	//Rivers
	std::vector<River> Rivers; // empty vector to hold river location and discharge time series
	int nriverblock = 0;

	//bnd
	
	
	bndparam rightbnd;
	bndparam leftbnd;
	bndparam topbnd;
	bndparam botbnd;
	


	//hot start
	double zsinit = -999.0; //init zs for cold start. if not specified by user and no bnd file =1 then sanity check will set to 0.0

	//Add a water level offset to initial conditions and bnds
	double zsoffset = 0.0;


	std::string hotstartfile;
	//std::string deformfile;
	int hotstep = 0; //step to read if hotstart file has multiple steps
	//other
	clock_t startcputime, endcputime;
	
	//Netcdf parameters
	int smallnc = 1;//default save as short integer if smallnc=0 then save all variables as float
	float scalefactor = 0.01f;
	float addoffset = 0.0f;

#ifdef USE_CATALYST
        // ParaView Catalyst parameters
        int use_catalyst = 0;
        int catalyst_python_pipeline = 0;
        int vtk_output_frequency = 0;
        double vtk_output_time_interval = 1.0;
        std::string vtk_outputfile_root = "bg_out";
        std::string python_pipeline = "coproc.py";
#endif

	// This is controlled by the sanity checker not directly by the user
	int resetmax = 0;
	int outhhmax = 0;
	int outzsmax = 0;
	int outuumax = 0;
	int outvvmax = 0;

	int outhhmean = 0;
	int outzsmean = 0;
	int outuumean = 0;
	int outvvmean = 0;

	int outvort = 0;

	// info of the mapped cf
	inputmap roughnessmap;

	forcingmap windU;
	forcingmap windV;
	forcingmap atmP;
	forcingmap Rainongrid;

	// deformation forcing for tsunami generation
	std::vector<deformmap> deform;
	double deformmaxtime = 0.0; // time after which no deformation occurs (internal parameter to cut some of the loops)

};



// End of global definition
#endif