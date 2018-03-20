/*
 * WICPS.cpp
 *Description: Client Code for Walk-in Clinic to use for managing patients. Utilizes ADT Classes Patient and List.
 * Last modified: May 29 2017
 * Authors: Hakeem Wewala, Josh Shercliffe
 */

#include <iostream>
#include <cctype>
#include "Patient.h"
#include "List.h"

using namespace std;

// Description: Add a patient to the list.
//              User is able to add one patient at a time. User must insert a valid care card number, or else the resulting
//              care card number will be all 0s. Care card number must not contain anything except a number of length 10.
void add(List* thePatients)
{
    string patientCareCard, patientName, patientAddress, patientEmail, patientPhone ="";

    //Create a new patient
    cout << " Please enter the new patient's 10-digit care card number: ";
    //Remove all leading whitespace
    getline(cin >> ws, patientCareCard);
    Patient thePatient(patientCareCard);

    cout << " Please enter the patient's name: ";
    getline(cin >> ws, patientName);
    thePatient.setName(patientName);

    cout << " Please enter the patient's address: ";
    getline(cin >> ws, patientAddress);
    thePatient.setAddress(patientAddress);

    cout << " Please enter the patient's email: ";
    getline(cin >> ws, patientEmail);
    thePatient.setEmail(patientEmail);

    cout << " Please enter the patient's phone number: ";
    getline(cin >> ws, patientPhone);
    thePatient.setPhone(patientPhone);

    if(thePatients->insert(thePatient))
        cout <<"The patient has been added to the list. " << endl;
    else
        cout <<"The patient's care card number already exists in the list or the list is full. " << endl;

    return;
}

// Description: Remove a patient or all patients within the list.
//              User is able to remove one patient by searching for them, or removing all patients.
void removeList(List* thePatients)
{
    string patientCareCard ="";

// Check if the patient list is empty.
    if (thePatients->getElementCount() != 0)
    {
        thePatients->printList();
        cout << "Please enter the care card number of the patient to remove from the list " << endl << "or enter 'all' to remove all patients from the list : ";
        getline(cin >> ws, patientCareCard);

        //Remove patient from list
        if(patientCareCard == "all")
        {
            thePatients->removeAll();
            cout << "All patients have been removed from the list. " << endl;
            return;
        }
        if (thePatients->remove(patientCareCard))
            cout << "Patient has been removed from the list. " << endl;
        else
            cout << "Patient not found in list. " << endl;
    }
    else
        cout << "There are no patients in the list yet. " << endl;

    return;
}

// Description: Search for a patient within the list.
//              User is able to search for patients within the list via their care card number.
void searchList(List* thePatients)
{
    string patientCareCard ="";
    Patient* searchPatient;

    cout << "Please enter the 10-digit care card number of the patient you would like to search: ";
    getline(cin >> ws, patientCareCard);

    searchPatient = thePatients->search(patientCareCard);
    if (searchPatient!= NULL)
    {
        cout << "Patient found info as follows: " << endl;
        searchPatient->printPatient();
    }
    else
    {
        cout << "No patient with care card number: " << patientCareCard << " was found in the list" << endl;
        return;
    }
}


// Description: Modify a patient within the list.
//              User is able to modify the patients Name, Address, Email, and Phone, but not their Care Card.
void modify(List* thePatients)
{
    string patientCareCard, patientName, patientAddress, patientEmail, patientPhone ="";
    Patient* searchPatient;
    char input = 0;
    cout << "Please enter the 10-digit care card number of the patient you would like to modify: ";
    // Search for the patient in the list.
    getline(cin >> ws, patientCareCard);
    // Search for the patient, and return NULL if no patient is found under that care card.
    searchPatient = thePatients->search(patientCareCard);
    // Print the options for the user
    if (searchPatient!= NULL)
    {
        cout << "Patient was found in list, what would you like to modify? " << endl;
        cout <<"To edit the patients name enter n" << endl;
        cout << "To edit the patients address enter a" << endl;
        cout <<"To edit the patients phone number enter p" << endl;
        cout << "To edit the patients email address enter e" << endl;
        cout << endl << endl;
        cout << "Your choice: ";
        cin >> input;

        if (input == 'n')
        {
            cout << " Please enter the patient's name: ";
            getline(cin >> ws, patientName);
            searchPatient->setName(patientName);
            return;
        }
        else if (input =='a')
        {
            cout << " Please enter the patient's address: ";
            getline(cin >> ws, patientAddress);
            searchPatient->setAddress(patientAddress);
            return;

        }
        else if (input == 'p')
        {
            cout << " Please enter the patient's phone number: ";
            getline(cin >> ws, patientPhone);
            searchPatient->setPhone(patientPhone);
            return;
        }
        else if (input =='e')
        {
            cout << " Please enter the patient's email: ";
            getline(cin >> ws, patientEmail);
            searchPatient->setEmail(patientEmail);
            return;
        }
        else
        {
            cout << "You entered an invalid option, returning to main menu. " << endl;
            return;
        }
    }
}




int main()
{

    // Variables declaration
    List* patients = new List();
    bool done = false;
    char input = 0;
    // Keep doing what the user selects until the user exits
    while (not done)
    {
        // Print menu to user
        cout << "To enter a new patient enter: a" << endl;
        cout << "To remove a patient or all patients enter: r" << endl;
        cout << "To search a patient enter: s" << endl;
        cout << "To modify a patient enter: m" << endl;
        cout << "To print the list of patients enter: p" << endl;
        cout << "To exit the application enter: x" << endl;
        cout << endl << endl;
        // Prompt user for their input
        cout << "Your choice: ";
        cin >> input;
        switch(input)
        {
        case 'a':
            add(patients);
            break;
        case 'r':
            removeList(patients);
            break;
        case 's':
            searchList(patients);
            break;
        case 'm':
            modify(patients);
            break;
        case 'p':
            patients->printList();
            break;
        case 'x':
            cout << "\n----Bye!\n" << endl;
            done = true;
            break;
        default:
            cout << "Not sure what you mean! Please, try again!" << endl;
        }
        // Always print out how many users there are in the list, for the user to keep track of
        cout << endl << "There are now " << patients->getElementCount() << " patients in the list." << endl << endl;
    }

    return 0;
}

