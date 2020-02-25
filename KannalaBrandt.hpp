#include "judgeKB.h"

class JudgeKB
{
public:
	JudgeKB();
	~JudgeKB();
	int setParameters(int image_width,
					  int image_height,
					  double k2,
					  double k3,
					  double k4,
					  double k5,
					  double mu,
					  double mv,
					  double u0,
					  double v0);
	int setParameters(char *path);

	bool jdThetaRegion();
	bool jdCoffRegion();
	bool jdConvergence();
	bool jdIteration();

private:
	int m_width;
	int m_height;
	double m_k2;
	double m_k3;
	double m_k4;
	double m_k5;
	double m_mu;
	double m_mv;
	double m_u0;
	double m_v0;

	double m_inv_K13;
	double m_inv_K22;
	double m_inv_K23;
	double m_inv_K11;

	int setInv();
	double fai(double px, double py, double theta);
	double fai(double r, double theta);
	double backprojectSymmetric(double r);
};

const char *kbGetVersion()
{
	return "V0.0.1-20200224133247";
}

KB_STATUS testKB(JudgeKB kb)
{
	if (kb.jdCoffRegion() == false)
	{
		return KB_CR;
	}
	if (kb.jdConvergence() == false)
	{
		return KB_CN;
	}
	if (kb.jdIteration() == false)
	{
		return KB_TH;
	}
	return KB_OK;
}

KB_STATUS kbTestParameters(int image_width,
						   int image_height,
						   double k2,
						   double k3,
						   double k4,
						   double k5,
						   double mu,
						   double mv,
						   double u0,
						   double v0)
{
	JudgeKB kb;
	if (kb.setParameters(image_width, image_height,
						 k2, k3, k4, k5,
						 mu, mv, u0, v0) == 0)
	{
		return testKB(kb);
	}
	return KB_ER;
}

KB_STATUS kbTestFile(char *file_path)
{
	JudgeKB kb;
	if (kb.setParameters(file_path) == 0)
	{
		return testKB(kb);
	}
	return KB_ER;
}