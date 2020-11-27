#include "cppunit/ui/text/TestRunner.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "string.h"
#include <stdio.h>


int main(int argc, char* argv[])
{	

	srand((unsigned int)0);
	bool bIsSuccessful;

	// Get test suites from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	if (1 == argc)
	{
		// Change the default outputter to a compiler error format outputter
		runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
		// Run the tests
		bIsSuccessful = runner.run();
	}
	else if (3 == argc && !strcmp("-o", argv[1]))
	{
		std::ofstream file(argv[2]);
		// Change the default outputter to a XML format outputter
		CppUnit::XmlOutputter* outputter = 
			new CppUnit::XmlOutputter(&runner.result(), file, argv[2]);
		runner.setOutputter(outputter);
		bIsSuccessful = runner.run();
		file.close();
	}
	else
	{
		std::cout << "Usage: [no argument] Run the unit test and write the result to the standard error output." << std::endl;
		std::cout << "	[-o xmlFile] Run the unit test and write the result to a XML format file.\n" << std::endl;
		std::cout << "\nExample: eCopIPLibTest.exe -o result.xml\n" << std::endl;
		return -1;
	}

	// Return error code 1 if the one of test failed.
	return 0;
}
