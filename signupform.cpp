#include "signupform.h"

signUpForm::signUpForm(QWidget *parent) : QWidget(parent)
{

    finishButton = new QPushButton("Finish");
    refreshButton = new QPushButton("Refresh");

    firstName = new QLabel("First Name");
    firstNameField = new QLineEdit();

    lastName = new QLabel("Last Name");
    lastNameField = new QLineEdit();

    dateOfBirth = new QLabel("Enter your birthdate");
    dateField = new QDateEdit(); //fix this to show more verbose date

    gender = new QLabel("Gender");
    genderFieldMale = new QRadioButton("Male");
    genderFieldFemale = new QRadioButton("Female");

    username = new QLabel("Username");
    usernameField = new QLineEdit();

    email = new QLabel("Email");
    emailField = new QLineEdit();

    password = new QLabel("Password");
    passwordField = new QLineEdit();


    textField = new QTextEdit();

    mainV = new QVBoxLayout;
    radioV = new QVBoxLayout;
    topGrid = new QGridLayout;

    //start of top grid
    topGrid->addWidget(firstName,0,0);
    topGrid->addWidget(firstNameField,0,1);

    topGrid->addItem(new QSpacerItem(40,10),0,2,1,1); //add a spacer between age and rest of widgets

    topGrid->addWidget(dateOfBirth,0,3);
    topGrid->addWidget(dateField,0,4);

    topGrid->addWidget(lastName,1,0);
    topGrid->addWidget(lastNameField,1,1);

    topGrid->addWidget(gender,2,0);
    //vertical box for radio buttons
    radioV->addWidget(genderFieldMale,0,0);
    radioV->addWidget(genderFieldFemale,1,0);
    //end of vertical box for radio buttons
    topGrid->addItem(radioV, 2, 1);

    topGrid->addWidget(refreshButton,3,0);
    //end of top grid

    //combine all three main elements in vertical box
    mainV->addItem(topGrid);
    mainV->addWidget(textField);
    mainV->addWidget(finishButton);

    setLayout(mainV);

    QObject::connect(refreshButton, SIGNAL(clicked(bool)), this, SLOT(signUp()));

}

void signUpForm::signUp()
{
    //check this for JSON interactions : https://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5
    //check if username exists - this must be unqiue
    //validate email
    //check necessary fileds are filled
    //check password for requirements
    QString error;

    QString fname = this->firstNameField->text();
    if (fname.isEmpty()) { error += "Fill in your first name please\n"; }
    QString lname = this->lastNameField->text();
    if (lname.isEmpty()) { error += "Fill in your last name please\n"; }
    QString dateOfBirth = this->dateField->text();
    QString gender = "Unspecified";

    if (this->genderFieldMale->isChecked()){
        gender = "Male";
    }
    else if (this->genderFieldFemale->isChecked()){
        gender = "Female";
    }

    if(error.isEmpty()){
        //success
        //write to file
    }else
    {
    this->textField->setText(error);
    }
};
