/*
* Marisa Kuyava
* CS 210
* 2/15/2022
*/

#include <Python.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;


	return 0; // _PyLong_AsInt(presult);
}


void menuDispaly() {
	/*Function to print menu to the console. Takes action based on user input 1, 2, 3 or 4
	* Re-prompts for user input if invalid input is entered.
	*/

	int menuOption; //takes input for menu choice

	system("Color 90"); // Changes background color to light blue and font to black
	cout << "|=======================================================================|" << endl;
	cout << "|=========================== MENU OPTIONS ==============================|" << endl;
	cout << "|====|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|====|" << endl;
	cout << "|====| 1) Print list of all purchased items and quantity purchased |====|" << endl;
	cout << "|====| 2) Choose product and print quantity purchased		   |====|" << endl;
	cout << "|====| 3) Display text histogram			  	   |====|" << endl;
	cout << "|====| 4) Exit program						   |====|" << endl;
	cout << "|====|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|====|" << endl;
	cout << "|=======================================================================|" << endl;
	cout << "|=======================================================================|" << endl;
	cout << endl;

	cin >> menuOption;

	/*Menu Option 1:
		Prints the total quantity of each product purchased that day and stored in a file
	 */
	if (menuOption == 1) {
		system("Color D0"); // Changes background color to light purple and font to black
		cout << endl;
		cout << "|====== TOTAL QUANTITY PURCHASED TODAY ======|" << endl;
		cout << endl;
		CallProcedure("read_File"); //reads the file in python
		cout << endl;
		cout << "|==================== END ===================|" << endl;
		cout << endl;
		system("pause");
	}
	/*Menu Option 2:
		Calls python function that will read a file, count and sort product amount
		then write to a .dat file, reads .dat file and creates a visual histogram
	*/
	else if (menuOption == 2) {
		system("Color 50");// Changes background color to purple and font to black
		string userString;
		cout << "What product would you like to look up? ";
		cout << endl;
		cin >> userString; //Captures user input 

		int totalItems = callIntFunc("locate_Total_Product_Amount", userString); //Gets frequency of user item from file

		if (totalItems == -1) {
			cout << "The item could not be located within the file. Returning to main menu." << endl; // Prints error if item is not found in file due to mispelling/not listed.
		}
		else {
			cout << endl;
			cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
			cout << "|  There were a total of " << totalItems << " " << userString << " sold today." << endl; //Prints product name/quantity purchased
			cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
			cout << endl;
		}
		system("pause");
	}

	else if (menuOption == 3) {
		system("Color 10");// Changes background color to blue and font to black
		cout << endl;
		cout << "|~~~~~~~~~~~~ HISTOGRAM ~~~~~~~~~~~~|" << endl;
		cout << endl;
		CallProcedure("read_AND_Write_File");
		cout << "|~~~~~~~~~~~~ END ~~~~~~~~~~~~|" << endl;
		cout << endl;
		system("pause");
	}
	else if (menuOption == 4) {
		cout << "Goodbye!" << endl; // Prints Goodbye
		exit(0);//Exits program
	}
	else {
		//Clear/ignore cin to avoid infinate loop if non-integer is entered by user
		cin.clear();
		cin.ignore();
		cout << endl;
		cout << "Invalid selection. Please enter 1, 2, 3 or 4." << endl;
		cout << endl;
	}
	menuDispaly(); // Re-displays menu for new user choice
}



int main()
{
	//starter code calls
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);

	//calls menu for main functionality of the program
	menuDispaly();

	return 0;
}