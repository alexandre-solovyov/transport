
#include <gtest/gtest.h>
#include <vehicle.h>

extern std::string DATA_DIR;

class VehiclesTest : public ::testing::Test
{
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F( VehiclesTest, time_is_ok )
{
	Vehicle boeing;
	boeing.A.resize(3);
	boeing.A[0] = 0.75*G;
	boeing.A[1] = 0;
	boeing.A[2] = -0.03*G;
	boeing.FC.resize(3);
	boeing.FC[0] = 11.0;
	boeing.FC[1] = 1.0;
	boeing.FC[2] = 0.25;
	boeing.GT = 2600;
	boeing.CV = 915;
	boeing.NP = 200;

	Info i = boeing.complete( 2884 );
	EXPECT_NEAR( 2884, i.distance/1000, 1E-3 ); //km
	EXPECT_NEAR( 3.276, i.time/3600, 1E-3 );    //hours
	EXPECT_NEAR( 8.301, i.fuel/1000, 1E-3 );    //tons

	EXPECT_NEAR( 2185.0, boeing.cost( 2884, 0.75 ), 1E0 );
}
