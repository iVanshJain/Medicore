#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <cgicc/Cgicc.h> 
#include <mysql.h>

//Insertion Data
	/*if (mysql_real_connect(conn, "localhost", "root", "", "medicore", 0, NULL, 0)!=NULL)
	{
		consolelog("Connection Successfully");
		if (mysql_query(conn,"INSERT INTO logindetails(email_id,pass) VALUES('medicore@gmail.com','medicore')") == 0)
		{
			consolelog("Inserted");
		}
		else {
			consolelog("Not Inserted");
		}
	}
	else {
		consolelog(mysql_error(conn));
	}*/


void consolelog(std::string data) {
	std::cout << "<script>";
	std::cout << "console.log('" << data << "');\n";
	std::cout << "</script>";
}
void ConfigurePage(std::string page_loc) {

	std::fstream file;
	file.open(page_loc);
	std::cout << "Content-type:text/html\r\n\r\n";

	for (std::string line; std::getline(file, line);)
	{
		std::cout << line << std::endl;
	}

}
void home() {

	std::list<long> headings = {30,50000,20};
	std::vector<std::string> reports;

	reports.push_back("There was a breakdown in the elevator on the 1st Floor");
	reports.push_back("There was a breakdown in the elevator on the 1st Floor");
	reports.push_back("There Was Damage To The Main Dooor");

	ConfigurePage("C:/xampp/cgi-bin/Medicore/html/home.html");

	int i = 0;
	for (int x : headings) {	
		std::cout << "<script>";
		std::cout << "document.getElementById('rep" << (i + 1) << "').innerHTML = '" << reports[i] << "';";
		std::cout << "document.getElementById('head" << (i + 1) << "').innerHTML = '" << x << "';";
		std::cout << "</script>";
		i++;
	}

}
int LoginCredentials(std::string email, std::string pass) {

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* result;

	conn = mysql_init(NULL);

	if (mysql_real_connect(conn, "localhost", "root", "", "medicore", 0, NULL, 0) != NULL)
	{
		if (mysql_query(conn, "SELECT * FROM logindetails") == 0)
		{
			result = mysql_store_result(conn);
			while ((row = mysql_fetch_row(result)) != NULL)
			{
				if (row[3] == email && row[4] == pass) {
					return 1;
				}
			}
		}
		else {
			consolelog("No Data");
		}
	}
	mysql_close(conn);
	return 0;
}

void login(cgicc::Cgicc cgicc_form)
{

	ConfigurePage("C:/xampp/cgi-bin/Medicore/html/login.html");


	cgicc::form_iterator email = cgicc_form.getElement("email");
	cgicc::form_iterator pass = cgicc_form.getElement("pass");

	if (LoginCredentials(email->getValue(), pass->getValue())==1) {
		std::cout << "<script>\n";
		std::cout << "Swal.fire(" << "'Medicore'," << "'Login Successfully'," << "'success').then(function(){window.location.href= 'index.cgi?page=home';});";
		std::cout << "</script>\n";
	}
	else {
		std::cout << "<script>\n";
		std::cout << "Swal.fire(" << "'Medicore'," << "'Invalid Credentials'," << "'error').then(function(){window.location.href= 'index.cgi?page=login';});";
		std::cout << "</script>\n";
	}

}

int Signup(std::string fname,std::string lname, std::string email, std::string pass) {

	MYSQL* conn;

	conn = mysql_init(NULL);

	std::string query = "INSERT INTO logindetails(fname,lname,email_id,pass) VALUES('"+fname+"','" + lname + "','" + email + "','" + pass + "')";

	if (mysql_real_connect(conn, "localhost", "root", "", "medicore", 0, NULL, 0) != NULL)
	{
		if (mysql_query(conn,query.c_str()) == 0)
		{
			return 1;
		}
	}
	mysql_close(conn);
	return 0;
}

void index(cgicc::Cgicc cgicc_form) {

	ConfigurePage("C:/xampp/cgi-bin/Medicore/html/index.html");

	cgicc::form_iterator fname = cgicc_form.getElement("first_name");
	cgicc::form_iterator lname = cgicc_form.getElement("last_name");
	cgicc::form_iterator email = cgicc_form.getElement("email");
	cgicc::form_iterator pass = cgicc_form.getElement("pass");

	bool termscheck = cgicc_form.queryCheckbox("termsch");

	if (!fname->isEmpty() && !lname->isEmpty() && !email->isEmpty() && !pass->isEmpty() && termscheck == true) {

		if (Signup(fname->getValue(), lname->getValue(), email->getValue(), pass->getValue()) == 1)
		{
			std::cout << "<script>\n";
			std::cout << "Swal.fire(" << "'Medicore'," << "'Registered Successfully'," << "'success').then(function(){window.location.href= 'index.cgi?page=login';});";
			std::cout << "</script>\n";
		}
		else {
			std::cout << "<script>\n";
			std::cout << "Swal.fire(" << "'Medicore'," << "'Something Went Wrong'," << "'success').then(function(){window.location.href= 'index.cgi?page=login';});";
			std::cout << "</script>\n";
		}

	}

}

void writeToPatientFile(std::string filename,int id,std::string name,int age, std::string gender) {

	std::ofstream fout(filename, std::ios::app);
	if (!fout) {
		std::cout << "Cannot open file for writing"<<std::endl;
		exit(EXIT_FAILURE);
	}
	fout << id << ' ' << name << ' ' << age << ' ' << gender << std::endl;
	fout.close();

}

void readFromPatientFile(std::string filename) {

	std::ifstream fin(filename, std::ios::in);

	if (!fin) {
		consolelog("Cannot open file for reading");
	}

	int id = 0,age=0;
	std::string name = "";
	std::string gender = "";

	std::cout << "<script>" << std::endl;
	std::cout << "var html = '';" << std::endl;
	std::cout << "html ='<table>'" << std::endl;
	std::cout << "+'<tr>'" << std::endl;
	std::cout << "+'<td>'+" << "'No'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'Name'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'Age'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'Gender'" << "+'</td>'" << std::endl;
	std::cout << "+'</tr>'" << std::endl;

	while (fin >> id >> name >> age >> gender) {
	
		std::cout << "+'<tr>'" << std::endl;
		std::cout << "+'<td>'" <<std::endl << "+'<h2>'+" << id << "+'</h2>'+" << std::endl <<"'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h2>'+'" << name << "'+'</h2>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h2>'+" << age << "+'</h2>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h2>'+'" << gender << "'+'</h2>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'</tr>'" << std::endl;
	}
	std::cout << "+'</table>';" << std::endl;
	std::cout << "$('#tablePatientdata').html(html);" << std::endl;
	std::cout << "</script>" << std::endl;

	fin.close();
}

void writeToAllPatientFile(std::string filename, int id, std::string name, int age, std::string gender, std::string datein, std::string city,std::string d_case) {

	std::ofstream fout(filename, std::ios::app);
	if (!fout) {
		std::cout << "Cannot open file for writing" << std::endl;
		exit(EXIT_FAILURE);
	}
	fout << id << ' ' << name << ' ' << age << ' ' << gender << ' ' << datein << ' ' << city << ' ' << d_case << std::endl;
	fout.close();

}

void readFromAllPatientFile(std::string filename) {

	std::ifstream fin(filename, std::ios::in);

	if (!fin) {
		consolelog("Cannot open file for reading");
	}

	int id = 0, age = 0;
	std::string name = "", gender = "", datein = "", city = "", d_case = "";

	std::cout << "<script>" << std::endl;
	std::cout << "var html2 = '';" << std::endl;
	std::cout << "html2 ='<table>'" << std::endl;
	std::cout << "+'<tr>'" << std::endl;
	std::cout << "+'<td>'+" << "'NO'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'NAME'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'GENDER'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'AGE'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'DATE IN'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'CITY'" << "+'</td>'" << std::endl;
	std::cout << "+'<td>'+" << "'CASE'" << "+'</td>'" << std::endl;
	std::cout << "+'</tr>'" << std::endl;

	while (fin >> id >> name >> age >> gender >> datein >> city >> d_case) {
		std::cout << "+'<tr>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+" << id << "+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+'" << name << "'+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+'" << gender << "'+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+" << age << "+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+'" << datein << "'+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+'" << city << "'+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'<td>'" << std::endl << "+'<h3>'+'" << d_case << "'+'</h3>'+" << std::endl << "'</td>'" << std::endl;
		std::cout << "+'</tr>'" << std::endl;
	}

	std::cout << "+'</table>';" << std::endl;
	std::cout << "$('#tableAllPatientdata').html(html2);" << std::endl;
	std::cout << "</script>" << std::endl;

	fin.close();
}

void patient()
{

	ConfigurePage("C:/xampp/cgi-bin/Medicore/html/patient.html");

	std::ofstream ofs;
	ofs.open("PatientList.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	std::ofstream ofs1;
	ofs1.open("AllPatientList.txt", std::ofstream::out | std::ofstream::trunc);
	ofs1.close();

	writeToPatientFile("PatientList.txt", 6, "AndreaBrewer", 40, "Male");
	writeToPatientFile("PatientList.txt", 7, "TimothyMiler", 36, "Male");
	writeToPatientFile("PatientList.txt", 8, "NickBarnett", 55, "Male");
	writeToPatientFile("PatientList.txt", 9, "DanielleEllis", 40, "Male");
	writeToPatientFile("PatientList.txt", 10, "VictoriaHawkins", 28, "Male");

	writeToAllPatientFile("AllPatientList.txt", 1, "GuyHawkins", 30, "Male","31/01/2021","Powai","Cough");
	writeToAllPatientFile("AllPatientList.txt", 2, "JaneCooper", 60, "Male", "08/06/2021","Ahemdabad","Fever");
	writeToAllPatientFile("AllPatientList.txt", 3, "RobertFox", 71, "Female", "11/07/2021", "Pune", "Cholera");
	writeToAllPatientFile("AllPatientList.txt", 4, "JulieRiley", 35, "Male", "10/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 5, "AlanFox", 25, "Male", "08/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 6, "AndreaBrewer", 40, "Male", "11/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 7, "TimothyMiler", 36, "Male", "09/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 8, "NickBarnett", 55, "Male", "11/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 9, "DanielleEllis", 40, "Male", "09/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 10, "VictoriaHawkins", 28, "Male", "10/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 11, "AndreaLych",56, "Male", "09/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 12, "TimothyGrand", 45, "Male", "09/11/2021", "Sonipat", "Dengue");
	writeToAllPatientFile("AllPatientList.txt", 13, "LouisaDean", 30, "Male", "10/11/2021", "Sonipat", "Dengue");

	readFromPatientFile("PatientList.txt");

	readFromAllPatientFile("AllPatientList.txt");

}

void aboutus() {
	ConfigurePage("C:/xampp/cgi-bin/Medicore/html/aboutus.html");
}
int main()
{
	cgicc::Cgicc formData;
	std::string page = formData.getEnvironment().getQueryString();

	if (page == "")
	{
		index(formData);
	}
	else if (page == "page=home")
	{
		home();
	}
	else if (page == "page=patient") {
		patient();
	}
	else if (page == "page=aboutus") {
		aboutus();
	}
	else if (page == "page=login") {
		login(formData);
	}

	return 0;
}

