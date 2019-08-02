#include "Histogram2D.hh"

//----------------------------
// Constructor
//----------------------------
Histogram2D::Histogram2D(string name, int binSizex, double minx, double maxx, int binSizey, double miny, double maxy)
	:name_(name),
	binSizex_(binSizex),
	minx_(minx),
	maxx_(maxx),
	binSizey_(binSizey),
	miny_(miny),
	maxy_(maxy)
{
	binWidthx_ = (maxx_-minx_)/double(binSizex_);
	binWidthy_ = (maxy_-miny_)/double(binSizey_);

	cout<<"Histogram "<<name_<<endl;

	cout<<"binSizex_ "<<binSizex_<<endl;
	cout<<"minx_ "	 <<minx_<<endl;
	cout<<"maxx_ "	 <<maxx_<<endl;
	cout<<"binWidthx_ "	 <<binWidthx_<<endl;

	cout<<"binSizey_ "<<binSizey_<<endl;
	cout<<"miny_ "	 <<miny_<<endl;
	cout<<"maxy_ "	 <<maxy_<<endl;
	cout<<"binWidthy_ "	 <<binWidthy_<<endl;

	for(int i=0;i<binSizey_;i++)
	{
		int xID = i;
		string hisyName = "hisx_" + to_string(xID); 
		Histogram hisy(hisyName,binSizey_,miny_,maxy_);
		histogramYs_.push_back(hisy);
	}
}

//----------------------------
// Deconstructor
//----------------------------
Histogram2D::~Histogram2D()
{}

//----------------------------
// Public
//----------------------------
void Histogram2D::Fill(double x, double y, double weight)
{
	// step 1 : locate X, which means locate the histogram in histogramYs_

	// step 1.1 : find the bin corresponding to the sample value
	int binxID = GetBinIDX(x);

	// step 1.2 : fill the weighth into current bin
	histogramYs_[binxID].Fill(y,weight);
}

//----------------------------
// Private : Tools
//----------------------------
int Histogram2D::GetBinIDX(double x)
{
	int binxID = -1;

	// step 1.1 : find the bin corresponding to the sample value
	for(int i=0;i<binSizex_;i++)
	{
		int binxIDCurrent = i;
		double minxCurrentBin = 0;
		double maxxCurrentBin = 0;
		int isBinBorderGood = GetBinX_Border(binxIDCurrent,minxCurrentBin,maxxCurrentBin);

		if(x>=minxCurrentBin&&x<maxxCurrentBin)
		{
			binxID = binxIDCurrent;
			break;
		}
	}

	return binxID;
}

//----------------------------
// Public
//----------------------------
void Histogram2D::Show()
{
	for(int i=0;i<binSizex_;i++)
	{
		int binxID = i;
		histogramYs_[binxID].Show();
	}
}

//----------------------------
// Private 
//----------------------------
int Histogram2D::GetBinX_Border(int currentBin, double &minCurrentBin, double &maxCurrentBin)
{
	if(currentBin<0) return 0;

	minCurrentBin = minx_ +  binWidthx_*(double(currentBin));
	maxCurrentBin = minx_ +  binWidthx_*(double(currentBin) + 1.);

	return 1;
}
