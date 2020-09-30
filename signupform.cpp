#include "signupform.h"

signUpForm::signUpForm(QWidget *parent) : QWidget(parent)
{

    submitButton = new QPushButton("Submit");

    userName = new QLabel("Username");
    userNameField = new QLineEdit();

    firstName = new QLabel("First Name");
    firstNameField = new QLineEdit();

    lastName = new QLabel("Last Name");
    lastNameField = new QLineEdit();

    dateOfBirth = new QLabel("Birthdate");
    dateField = new QDateEdit(); //fix this to show more verbose date

    profilePic = new QLabel("Profile Pic ");
    profilePicField = new QLineEdit();

    gender = new QLabel("Gender");
    genderFieldMale = new QRadioButton("Male");
    genderFieldFemale = new QRadioButton("Female");

    password = new QLabel("Password");
    passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);

    email = new QLabel("Email");
    emailField = new QLineEdit();

    textField = new QTextEdit();

    mainV = new QVBoxLayout;
    radioV = new QVBoxLayout;
    topGrid = new QGridLayout;

    //start of top grid

    topGrid->addWidget(userName,0,0);
    topGrid->addWidget(userNameField,0,1);

    topGrid->addWidget(firstName,1,0);
    topGrid->addWidget(firstNameField,1,1);

    topGrid->addItem(new QSpacerItem(40,10),0,2,1,1); //add a spacer between age and rest of widgets

    topGrid->addWidget(dateOfBirth,2,3);
    topGrid->addWidget(dateField,2,4);

    topGrid->addWidget(lastName,2,0);
    topGrid->addWidget(lastNameField,2,1);

    topGrid->addWidget(password,3,0);
    topGrid->addWidget(passwordField,3,1);

    topGrid->addWidget(email,0,3);
    topGrid->addWidget(emailField,0,4);

    topGrid->addWidget(gender,4,3);
    //vertical box for radio buttons
    radioV->addWidget(genderFieldMale,0,0);
    radioV->addWidget(genderFieldFemale,1,0);
    //end of vertical box for radio buttons
    topGrid->addItem(radioV, 4, 4);

    topGrid->addWidget(profilePic,1,3);
    topGrid->addWidget(profilePicField,1,4);



    topGrid->addWidget(submitButton,4,0);

    //end of top grid

    //combine all three main elements in vertical box
    mainV->addItem(topGrid);
    mainV->addWidget(textField);
    //mainV->addWidget(submitButton);

    setLayout(mainV);

    //QObject::connect(refreshButton, SIGNAL(clicked(bool)), this, SLOT(signUp()));

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
