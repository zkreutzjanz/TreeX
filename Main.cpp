// Your First C++ Program

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

string fancyDisplayBoxes(vector<string> headers,int width);

string stringNTimes(string input,int count);
class Family;
void startup();
class atr{
	private:
		vector<atr> subAtr;
		string tag;
		string body;
	public:
		
		atr(){};
	
		atr(string myTag,string myBody):tag(myTag),body(myBody){};
		
		string getTag(){return tag;}
		string getBody(){return body;}
		vector<atr> getSubAtrs(){return subAtr;	}
		void setTag(string myTag){tag = myTag;}
		void setBody(string myBody){body = myBody;}
		void addAtr(atr myAtr){subAtr.push_back(myAtr);}
		
		void addAtrAtLevel(atr myAtr,int level){
			if(level==0){
				addAtr(myAtr);
			}else{
				--level;
				if(subAtr.empty()){
					addAtr(atr(" "," "));
				}
				subAtr[subAtr.size()-1].addAtrAtLevel(myAtr,level);
			}
		}
		
		string getNestedAtrsString(string current,string buffer){
			string val = current+tag+": "+body+"\n";
			for(atr myAtr : subAtr){
				val = val +myAtr.getNestedAtrsString(current+buffer,buffer);
			}
			return val;
		}
};

class dataEntry{
	
	public:
		int numeral;
		string tag;
		string body;
		
		/**
		* Type:
		* 	Constructor
		* Class:
		*	dataEntry
		* Constructor:
		* 	dataEntry
		*
		**/
		dataEntry(){};
		dataEntry(string input){
			parseLine(input);
			
		};
		
		/**
		* Type:
		* 	Function
		* Class:
		*	dataEntry
		* Function:
		* 	parseLine
		* Parameters: 
		*	(string) input: the string to input
		* Return:
		* 	Nothing
		* Abstract:
		* 	Takes a string and parses it to the "dataEntry" object. "input" should be formatted as: "{integer} {string} [{string}]". 
			First integer goes to "numeral" integer. First " " seperated string goes to "tag". rest of string goes to "body".
		*
		* Exceptions:
		* 	Will fail if first string seperated by a " " is NaN
		**/
		void parseLine(string input){
			
			int iteration=0;
			string primVal;
			string secVal;
			string tertVal;
			for(int i = 0;i < input.length() ;i++){
				
				if(iteration==1){
					
					if(input[i]==' '){
						tertVal= input.substr(i+1,input.length()-i-1);
						i = input.length();
					}
					else{
						secVal.push_back(input[i]);
					}
				}else if(iteration==0){
					if(input[i]==' '){
						iteration++;
					}else{
						primVal.push_back(input[i]);
					}
				}
			}
			numeral=stoi(primVal);
			tag = secVal;
			body = tertVal;
		}
		
};

class Person;

class Person{
	private:
		vector<atr> personAtrs;
		string id;
		
		Family *FAMC;
		vector<Family *> FAMS;
		
	public:
	
		Person(string myId):id(myId){};
		Person(){};
		
		vector<atr> getPersonAtrs(){return personAtrs;}
		void setID(string myId){id = myId;}
		string getID(){return id;}
		void setFAMC(Family *myFAMC){FAMC=myFAMC;}
		Family* getFAMC(){return FAMC;}	
		void addFAMS(Family *myFAMS){FAMS.push_back(myFAMS);}
		vector<Family *> getFAMS(){return FAMS;}
		void addAtr(atr myAtr){personAtrs.push_back(myAtr);}
		
		void addAtrAtLevel(atr myAtr,int level){
			if(level==0){
				addAtr(myAtr);
			}else{
				--level;
				if(personAtrs.empty()){
					addAtr(atr("",""));
				}
				personAtrs[personAtrs.size()-1].addAtrAtLevel(myAtr,level);
			}
		}
		
		void clear(){
			personAtrs.clear();
			id = "";
			FAMC = NULL;
			FAMS.clear();
		}
		
		vector<string> getQueryProfile(){
			vector<string> val;
			val.push_back(id);
			val.push_back(getBodyFromAtrList({"NAME"}));
			val.push_back(getBodyFromAtrList({"BIRT","DATE"}));
			
		}
		
	    string getBodyFromAtrList(vector<string> atrList){
			atr currentAtr;
			for(string str:atrList){
				if(currentAtr.getTag()==""){
					for(atr a:personAtrs){
						if(a.getTag()==str){
							currentAtr = a;
						}
					}
				}else{
					for(atr a:currentAtr.getSubAtrs()){
						if(a.getTag()==str){
							currentAtr = a;
						}
					}
				}
			}
			if(currentAtr.getTag()==atrList[atrList.size()-1]){
				return currentAtr.getBody();
			}else{
				return "";
			}
		}
		
		

		string getProfileWithID(){
			string val = id;
			val = val+": "+getSimpleProfile();
			return val;
			
		}
		string getSimpleProfile(){
			string val = "";
			 for(atr myAtr : personAtrs){
				if(myAtr.getTag()=="NAME"){
					 val = val+myAtr.getBody()+", ";
				}
			 }
			 val = val+": ";
			 for(atr myAtr : personAtrs){
				if(myAtr.getTag()=="BIRT"){
					for(atr mySubAtr : myAtr.getSubAtrs()){
						if(mySubAtr.getTag()=="DATE"){
							val = val+mySubAtr.getBody()+", ";
						}
					}
				}
			 }
			 val = val;
			 
			return val;
		}
		string getRawProfile(){
			string rawProfile;
			for(atr myAtr : personAtrs){
				rawProfile = rawProfile+myAtr.getNestedAtrsString("","  ");
			}
			return rawProfile;
		}
		
		
		
		
};

class Family{
	
	private:
		Person *HUSB;
		Person *WIFE;
		
		string id;
		
		string HID;
		string WID;
		
		vector<string> CIDS;
		
	public:
		Family(){HID=" ";WID=" ";};
		
		vector<Person *> CHIL;
		
		void addCHIL(Person *myCHIL){}
		string getHID(){return HID;}	
		void setHID(string myHID){HID=myHID;}
		string getWID(){return WID;}	
		void setWID(string myWID){WID=myWID;}
		void addCIDS(string myCID){CIDS.push_back(myCID);}
		vector<string> getCIDS(){return CIDS;}
		void setID(string myId){id = myId;}
		string getID(){return id;}
		Person* getHUSB(){return HUSB;}	
		void setHUSB(Person *myHUSB){HUSB=myHUSB;}
		Person* getWIFE(){return WIFE;}	
		void setWIFE(Person *myWIFE){WIFE=myWIFE;}

		void clear(){
			HUSB = NULL;
			WIFE = NULL;
			HID = "";
			WID ="";
			CIDS.clear();
			CHIL.clear();
		}

		
		void addAtr(atr myAtr){
			if(myAtr.getTag()=="HUSB"){
				HID = myAtr.getBody();
			}
			if(myAtr.getTag()=="WIFE"){
				WID = myAtr.getBody();
			}
			if(myAtr.getTag()=="CHIL"){
				CIDS.push_back(myAtr.getBody());
			}
		}
};

class genealogicalTree{
	private:
		string sourceFileName;
		vector<dataEntry> importedLines;
		vector<Person> people;
		vector<Family> families;
		
	
	public:
		genealogicalTree(){};
		
		void setSourceFileName(string input){sourceFileName=input;}
		string getSourceFileName(){return sourceFileName;}
		
		
		//Startup functions
		
		void parseFile(){

			ifstream myFile;
			myFile.open(sourceFileName);
			string line;
			while( getline (myFile,line)){
				dataEntry temp = dataEntry();
				temp.parseLine(line);
				// new dataEntry().parseLine(); ??
				importedLines.push_back(temp);
			}
		}
		
		void createUnlinkedTree(){
			Person currentPerson = Person();
			Family currentFamily = Family();
			string currentType = "";
			for(dataEntry line : importedLines){
				if(line.numeral==0){
					currentType=line.body;
					if(currentType=="INDI"){
						people.push_back(currentPerson);
						currentPerson.clear();
						currentPerson.setID(line.tag);
					}else if(currentType=="FAM"){
						families.push_back(currentFamily);
						currentFamily.clear();
						currentFamily.setID(line.tag);
					}
				}else{
					if(currentType=="INDI"){
						currentPerson.addAtrAtLevel(atr(line.tag,line.body),line.numeral-1);
					}else if(currentType=="FAM"){
						currentFamily.addAtr(atr(line.tag,line.body));
					}
				}
			}
		}
		
		void linkTreeObjects(){
			for(int j = 0;j<families.size();j++){
				//cout<<"FAM\n";
				for(int i =0;i<people.size();i++){
					if(people[i].getID()==families[j].getHID()){
						people[i].addFAMS(&families[j]);
						families[j].setHUSB(&people[i]);
						//cout<<"  HUSB: "<<people[i].getID()<<"\n";
						//cout<<"  HUSB: "<<fam.getHUSB()->getID()<<"\n";
					}else 
					if(people[i].getID()==families[j].getWID()){
						people[i].addFAMS(&families[j]);
						families[j].setWIFE(&people[i]);
						//cout<<"  WIFE: "<<people[i].getID()<<"\n";
					}
					for(string CID : families[j].getCIDS()){
						if(people[i].getID()==CID){
							people[i].setFAMC(&families[j]);
							families[j].CHIL.push_back(&people[i]);
							//cout<<"  CHIL: "<<people[i].getID()<<"\n";
						}
					}
				}
			}
		}
		
		
		//Helpful Relational functions
		
		string generateAncestryView(Person *p,string base,string branch,string leaf,string air,int gend){
			string val;
			if(gend==2){
				
				if(p->getFAMC()){if(p->getFAMC()->getHID()!=""){
				    val += generateAncestryView(p->getFAMC()->getHUSB(),base+air,branch,leaf,air,1);
				}}
				val = val+"\n"+base+leaf+p->getID()+": "+p->getBodyFromAtrList({"NAME"});
				if(p->getFAMC()){if(p->getFAMC()->getWID()!=""){
					val = val+ generateAncestryView(p->getFAMC()->getWIFE(),base+air,branch,leaf,air,0);
				}}
				
			}else if(gend==1){
				
				if(p->getFAMC()){if(p->getFAMC()->getHID()!=""){
				    val += generateAncestryView(p->getFAMC()->getHUSB(),base+air,branch,leaf,air,1);
				}}
				val = val+"\n"+base+leaf+p->getID()+": "+p->getBodyFromAtrList({"NAME"});
				if(p->getFAMC()){if(p->getFAMC()->getWID()!=""){
					val = val+ generateAncestryView(p->getFAMC()->getWIFE(),base+branch,branch,leaf,air,0);
				}}
				
			}else if(gend==0){
				
				if(p->getFAMC()){if(p->getFAMC()->getHID()!=""){
				    val += generateAncestryView(p->getFAMC()->getHUSB(),base+branch,branch,leaf,air,1);
				}}
				val = val+"\n"+base+leaf+p->getID()+": "+p->getBodyFromAtrList({"NAME"});
				if(p->getFAMC()){if(p->getFAMC()->getWID()!=""){
					val = val+ generateAncestryView(p->getFAMC()->getWIFE(),base+air,branch,leaf,air,0);
				}}
			}
			return val;
		}
		
		string generateDescendancyView(Person *p,string base,string branch,string leaf,string air,string recent){
			
			string val = "\n"+base+leaf+p->getID()+": "+p->getBodyFromAtrList({"NAME"});
			//cout<<"test:"<<val<<"\n";
			if(p->getFAMS().size()!=0){
				//cout<<"Passed FAMS";
				for(int j=0;j<p->getFAMS().size();j++){
					
					if(p->getFAMS()[j]->getWIFE()->getID()!=p->getID()){
						val = val+"\n"+base+"  -"+p->getFAMS()[j]->getWIFE()->getID()+": "+p->getFAMS()[j]->getWIFE()->getBodyFromAtrList({"NAME"});
					}
					if(p->getFAMS()[j]->getHUSB()->getID()!=p->getID()){
						val = val+"\n"+base+"  -"+p->getFAMS()[j]->getHUSB()->getID()+": "+p->getFAMS()[j]->getHUSB()->getBodyFromAtrList({"NAME"});
					}
					for(int i =0;i<p->getFAMS()[j]->CHIL.size();i++){
						//cout<<"Chil"<<i;
						if(p->getFAMS()[0]->CHIL[i]){
							//cout<<"Passed CHIL";
							if(i==p->getFAMS()[j]->CHIL.size()-1){
								val = val + generateDescendancyView(p->getFAMS()[j]->CHIL[i],base+recent,branch,leaf,air,air);
							}else{
								val = val + generateDescendancyView(p->getFAMS()[j]->CHIL[i],base+recent,branch,leaf,air,branch);
							}
								
						}
					}
				}
				
			}
			//cout<<"returning";
			return val;
			
		}
	 
		
		//Displays
		
		void displaySourceFileSetPage(){
			
			system("cls");
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Source File Set Page"
			},20);
			cout<<fancyDisplayBoxes({
				"To go to main menu press \"0\"",
				"Otherwise enter new tree path below"
			},60)<<">";
			
			//handle input
			string input;
			cin>>input;
			if(input=="0"){
				displayMainMenu();
			}else{
				
			}
		}
	 
		void displayProfilePage(Person *p){
			system("cls");
			
			//get basic profile data
			vector<string> profileHeaders = {
				"Name: "+p->getBodyFromAtrList({"NAME"}),
				"Birth Date: "+p->getBodyFromAtrList({"BIRT","DATE"}),
				"Birth Place: "+p->getBodyFromAtrList({"BIRT","PLAC"})
			};
			if(p->getBodyFromAtrList({"DEAT","DATE"})!=""){profileHeaders.push_back("Death Date: "+p->getBodyFromAtrList({"DEAT","DATE"}));}
			if(p->getBodyFromAtrList({"DEAT","PLAC"})!=""){profileHeaders.push_back("Death Place: "+p->getBodyFromAtrList({"DEAT","PLAC"}));}
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Profile Page"
			},16);
			cout<<fancyDisplayBoxes({
				"Profile Data"
			},20);
			cout<<fancyDisplayBoxes(
				profileHeaders
			,100);
			
			//display Graphics: programatical children display
			if(p->getFAMS().size()!=0){
				cout<<fancyDisplayBoxes({"Children"},20);
				vector<string> childrenEntries;
				for(int i =0;i<p->getFAMS()[0]->CHIL.size();i++){
					if(p->getFAMS()[0]->CHIL[i]){
						int currentNum = i+1;
						//string topush = to_string(i+1)+":"+(p->getFAMS()[0]->CHIL[i]->getBodyFromAtrList({"NAME"}));
						//the following uses pointers
						childrenEntries.push_back(to_string(i+1)+":"+(p->getFAMS()[0]->CHIL[i]->getBodyFromAtrList({"NAME"})));
					}
				}
				cout<<fancyDisplayBoxes(childrenEntries,100);
			}
			
			//display Graphics: programatical Mother display
			if(p->getFAMC()){if(p->getFAMC()->getWID()!=""){
				cout<<fancyDisplayBoxes({"Mother"},20);
				cout<<fancyDisplayBoxes({(p->getFAMC()->getWIFE()->getBodyFromAtrList({"NAME"}))},100);
			}}
			
			//display Graphics: programatical Father display
			if(p->getFAMC()){if(p->getFAMC()->getHID()!=""){
				cout<<fancyDisplayBoxes({"Father"},20);
				cout<<fancyDisplayBoxes({(p->getFAMC()->getHUSB()->getBodyFromAtrList({"NAME"}))},100);
			}}
			
			//display Graphics: Options display
			cout<<fancyDisplayBoxes({
				"Options"
			},20);
			cout<<fancyDisplayBoxes({
				"1: Go to Mother's Profile Page",
				"2: Go to Father's Profile Page",
				"3: View Ancestry",
				"4: View Descendacy",
				"5: Go to Children Page",
				"6: Go to Main Menu",
				"7: Go to Raw Profile Page"
			},50)<<">";
			
			
			//handle Input
			int option;
			cin>>option;
			if(option == 1){
				if(p->getFAMC()){if(p->getFAMC()->getWID()!=""){
					displayProfilePage(p->getFAMC()->getWIFE());
				}}else{
					displayFailurePage("Person does not have Mother or WIFE pointer Broken",p);
				}
			}else if(option==2){
				if(p->getFAMC()){if(p->getFAMC()->getHID()!=""){
					displayProfilePage(p->getFAMC()->getHUSB());
				}}else{
					displayFailurePage("Person does not have Father or HUSB pointer Broken",p);
				}
			}else if(option==3){
				displayAncestryPage(p);
			}else if(option==4){
				displayDescendancyPage(p);
			}else if(option ==5){
				displayChildrenPage(p);
			}else if(option==6){
				displayMainMenu();
			}else if(option==7){
				displayRawProfilePage(p);
			}else{
				displayFailurePage("Entered invalid Option",p);
			}
			
		}
		
		void displayRawProfilePage(Person *p){
			system("cls");
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Raw Profile Page"
			},20);
			cout<<p->getRawProfile();
			cout<<fancyDisplayBoxes({
				"Options"
			},40);
			cout<<fancyDisplayBoxes({
				"-1: Go Back",
				"0: Go to Main Menu"
			},60)<<">";
			
			//handle input
			string input;
			cin>>input;
			if(input=="-1"){
				displayProfilePage(p);
			}else if(input=="0"){
				displayMainMenu();
			}else{
				displayFailurePage("Entered invalid Option",p);
			}
			
		}
		
		void displayFailurePage(string message){
			system("cls");
			
			//display Graphics
			cout<<"Failure. Details: "<<message+"\n";
			cout<<fancyDisplayBoxes({
				"Options"
			},20);
			cout<<fancyDisplayBoxes({
				"0. Go to Main Menu"
			},50)<<">";
			
			//handle Input
			int option;
			cin>>option;
			if(option==0){
				displayMainMenu();
			}else{
				displayFailurePage("Entered invalid Option, did you check that you are entering a UTF-8 \"0\" character?");
			}
		}
		
		void displayFailurePage(string message,Person *p){
			system("cls");
			
			//display Graphics
			cout<<"Failure. Details: "<<message+"\n";
			cout<<fancyDisplayBoxes({
				"Options"
			},20);
			cout<<fancyDisplayBoxes({
				"-1: Go Back",
				"0. Go to Main Menu"
			},50)<<">";
			
			//handle Input
			int option;
			cin>>option;
			if(option== -1){
				displayProfilePage(p);
			}else if(option==0){
				displayMainMenu();
			}else{
				displayFailurePage("Entered invalid Option, did you check that you are entering a UTF-8 \"0\" character?");
			}
		}
		
		void displayAncestryPage(Person *p){
			system("cls");
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Ancestry Page"
			},20);
			cout<<generateAncestryView(p,"","    |","    +","     ",2)<<"\n";
			cout<<"    1    2    3    4    5    6    7    8    9    0    1    2    3    4    5    6    7    8    9    0    1    2    3    4    5\n";
			cout<<fancyDisplayBoxes({
				"Options"
			},20);
			cout<<fancyDisplayBoxes({
				"-1: Go Back",
				"0: Go to Main Menu"
			},50)<<">";
			
			//handle input
			int option;
			cin>>option;
			if(option== -1){
				displayProfilePage(p);
			}else if(option == 0){
				displayMainMenu();
			}else{
				displayFailurePage("Entered invalid Option",p);
			}
		}
		
		void displayDescendancyPage(Person *p){
			system("cls");
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Descendany Page"
			},20);
			int startID =1;
			int *IDing;
			cout<<generateDescendancyView(p,"","  |","  +","   ","   ")<<"\n";
			cout<<"  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0\n";
			cout<<fancyDisplayBoxes({
				"Options"
			},20);
			cout<<fancyDisplayBoxes({
				"-1: Go Back",
				"0: Go to Main Menu"
			},50)<<">";
			
			//handle input
			int option;
			cin>>option;
			if(option== -1){
				displayProfilePage(p);
			}else if(option == 0){
				displayMainMenu();
			}else{
				displayFailurePage("Entered invalid Option",p);
			}
		}
		
		void displayChildrenPage(Person *p){
			system("cls");
			
			if(p->getFAMS().size()!=0){
				
				//generate children results array
				vector<string> childrenEntries;
				vector<Person *> children;
				int childrenCount = 0;
				for(int j=0;j<p->getFAMS().size();j++){for(int i =0;i<p->getFAMS()[j]->CHIL.size();i++){
					if(&p->getFAMS()[j]->CHIL[i]){
						children.push_back(p->getFAMS()[j]->CHIL[i]);
						childrenEntries.push_back(to_string(childrenCount+1)+":"+(p->getFAMS()[j]->CHIL[i]->getBodyFromAtrList({"NAME"})));
						childrenCount++;
					}
				}}
				
				//display Graphics
				cout<<fancyDisplayBoxes({
					"Children Page"
				},20);
				cout<<fancyDisplayBoxes({
					"Children"
				},20);
				cout<<fancyDisplayBoxes(
					childrenEntries
				,100);
				
				cout<<fancyDisplayBoxes({
					"Options"
				},20);
				cout<<fancyDisplayBoxes({
					"-1: Go Back",
					"0: Go to Main Menu",
					"Enter Children Number to Navigate to their Profile"
				},60)<<">";
				
				
				//handle input
				int option;
				cin>>option;
				if(option== -1){
					displayProfilePage(p);
				}else if(option==0){
					displayMainMenu();
				}else if(option<childrenEntries.size()+1){
					displayProfilePage(children[option-1]);
				}else{
					displayFailurePage("Entered invalid Option",p);
				}
			}else{
				cout<<fancyDisplayBoxes({"Options"},20);
				vector<string> optionHeaders = {
					"0. Go Back, No Children"
				};
				cout<<fancyDisplayBoxes(optionHeaders,50)<<">";
				int option;
				cin>>option;
				if(option==0){
					displayProfilePage(p);
				}else {
					displayFailurePage("Entered invalid Option",p);
				}
			}
			
		}
		
		void displaySearchPage(){
			
			system("cls");
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Search Page"
			},20);
			cout<<fancyDisplayBoxes({
				"Options"
			},40);
			cout<<fancyDisplayBoxes({
				"0: Go Back to Main Menu",
				"Other: Search Term to be Found"
			},60)<<">";
			
			//handle Input
			string input;
			cin>>input;
			if(input=="0"){
				displayMainMenu();
			}else{
				displaySearchResultPage(input);
			}
		}
		
		void displaySearchResultPage(string searchTerm){
			system("cls");
			
			//generate search results array
			vector<string> results;
			vector<Person> resultsPeople;
			int resultCount = 0;
			for(int i =0;i<people.size();i++){
				if(people[i].getBodyFromAtrList({"NAME"}).find(searchTerm)!= string::npos){
					results.push_back(to_string(resultCount+1)+":"+people[i].getBodyFromAtrList({"NAME"}));
					resultsPeople.push_back(people[i]);
					resultCount++;
				}
			}
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Search Results Page"
			},25);
			cout<<fancyDisplayBoxes({"Results"},20);
			cout<<fancyDisplayBoxes(
				results
			,100);
			cout<<fancyDisplayBoxes({
				"Options"
			},20);
			cout<<fancyDisplayBoxes({
				"0: Go to Main Menu",
				"Result Number: Navigates to their Profile Page"
			},60)<<">";
		
		
			//handle Input
			int option;
			cin>>option;
			if(option==0){
				displaySearchPage();
			}else if(option<resultsPeople.size()+1){
				displayProfilePage(&resultsPeople[option-1]);
			}else{
				displayFailurePage("Entered invalid Option");
			}
			
			
		}
			
		void displayMainMenu(){
			system("cls");
			
			//display Graphics
			cout<<fancyDisplayBoxes({
				"Main Menu"
			},20);
			cout<<fancyDisplayBoxes({
				"Options"
			},40);
			cout<<fancyDisplayBoxes({
				"1: Go to Search Page",
				"2: Leave Tree"
			},60)<<">";
			
			//handle input
			string input;
			cin>>input;
			if(input=="1"){
				displaySearchPage();
			}if(input=="2"){
				startup();
			}else{
				displayFailurePage("Entered invalid Option");
			}
		}
	
	
};


//UI Elements
string fancyDisplayBoxes(vector<string> headers,int width){
	string val = "+"+stringNTimes("-",width-2)+"+\n";
	for(int i =0;i<headers.size();i++){
		val = val+"| "+headers[i]+stringNTimes(" ",width-4-headers[i].size())+" |\n";
		val = val+"+"+stringNTimes("-",width-2)+"+\n";
	}
	return val;
}

string stringNTimes(string input,int count){
	string val;
	for(int i=0;i<count;i++){
		val = val+input;
	}
	return val;
}


//currently not used
void startup(){
	system("cls");
	genealogicalTree startupTree = genealogicalTree();		
	//display Graphics
	cout<<fancyDisplayBoxes({
		"Startup"
	},20);
	cout<<fancyDisplayBoxes({
		"Options"
	},40);
	cout<<fancyDisplayBoxes({
		"1: Shut Down",
		"2: Load Default Tree",
		"3: Set Tree Path",
		"4: Open Tree"
	},60)<<">";
	/**
	if(input=="1"){
		return 0;
	}if(input=="2"){
		startup();
	}**/
}





#include <string>
int main() {
	
	//genealogicalTree defaultTree = genealogicalTree();
	//defaultTree.displayMainMenu();
	//transition to startup fx soon
	
	genealogicalTree myTree = genealogicalTree();
	myTree.setSourceFileName("mytree.txt");
	myTree.parseFile();
	myTree.createUnlinkedTree();
	myTree.linkTreeObjects();
	myTree.displayMainMenu();

	
    return 0;
}


