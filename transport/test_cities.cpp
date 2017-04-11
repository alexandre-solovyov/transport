
#include <gtest/gtest.h>
#include <cities.h>
#include <tools.h>

extern std::string DATA_DIR;

class CitiesTest : public ::testing::Test
{
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F( CitiesTest, city_is_valid )
{
	City c;

	c = City( "" );
	ASSERT_FALSE( c.isValid() );
	ASSERT_EQ( std::string( "" ), toS( c.name() ) );

	c = City( "test" );
	ASSERT_TRUE ( c.isValid() );
	ASSERT_EQ( std::string( "test" ), toS( c.name() ) );

	c = City( " " );
	ASSERT_FALSE( c.isValid() );
	ASSERT_EQ( std::string( "" ), toS( c.name() ) );

	c = City( "  " );
	ASSERT_FALSE( c.isValid() );
	ASSERT_EQ( std::string( "" ), toS( c.name() ) );

	c = City( "  abc d " );
	ASSERT_TRUE( c.isValid() );
	ASSERT_EQ( std::string( "abc d" ), toS( c.name() ) );
}

const std::wstring MSK;
TEST_F( CitiesTest, loading_is_ok )
{
	Cities* c = Cities::get();

	ASSERT_TRUE( c!=NULL );

	ASSERT_FALSE( c->load( "not_existing.dat" ) );
  ASSERT_TRUE( c->load( DATA_DIR + "cities.dat" ) );

	ASSERT_EQ( 311, c->size() );

	City t = c->find( MSK );
	ASSERT_EQ( MSK, t.name() );
}
