#include "signupform.h"
#include "loginpage.h"
#include "welcomepage.h"
#include "user.h"
#include <QCryptographicHash>
#include <qjsondocument.h>

signUpForm::signUpForm(QWidget *parent) : QWidget(parent)
{

    submitButton = new QPushButton("Submit");
    backButton = new QPushButton("Back");
    browseButton = new QPushButton("Browse");


    userName = new QLabel("Username");
    userNameField = new QLineEdit();

    firstName = new QLabel("First Name");
    firstNameField = new QLineEdit();

    lastName = new QLabel("Last Name");
    lastNameField = new QLineEdit();

    dateOfBirth = new QLabel("Birthdate");
    dateField = new QCalendarWidget();

    profilePic = new QLabel("Profile Pic ");
    profilePicField = new QLineEdit();

    gender = new QLabel("Gender");
    genderFieldMale = new QRadioButton("Male");
    genderFieldFemale = new QRadioButton("Female");

    password = new QLabel("Password");
    passwordField = new QLineEdit();
    passwordField->setEchoMode(QLineEdit::Password);

    confirmPassword = new QLabel("Confirm Password");
    confirmPasswordField = new QLineEdit();
    confirmPasswordField->setEchoMode(QLineEdit::Password);

    email = new QLabel("Email");
    emailField = new QLineEdit();

    error = new QLabel();
    error->setStyleSheet("QLabel {color : red;}");
    error->setVisible(false);

    mainV = new QVBoxLayout;
    radioV = new QVBoxLayout;
    topGrid = new QGridLayout;

    //start of top grid

    topGrid->addWidget(userName,0,0);
    topGrid->addWidget(userNameField,0,1);

    topGrid->addWidget(firstName,1,0);
    topGrid->addWidget(firstNameField,1,1);

    topGrid->addWidget(dateOfBirth,8,0);
    topGrid->addWidget(dateField,8,1);

    topGrid->addWidget(lastName,2,0);
    topGrid->addWidget(lastNameField,2,1);

    topGrid->addWidget(password,3,0);
    topGrid->addWidget(passwordField,3,1);

    topGrid->addWidget(confirmPassword,4,0);
    topGrid->addWidget(confirmPasswordField,4,1);

    topGrid->addWidget(email,5,0);
    topGrid->addWidget(emailField,5,1);

    topGrid->addWidget(gender,7,0);
    //vertical box for radio buttons
    radioV->addWidget(genderFieldMale,0,0);
    radioV->addWidget(genderFieldFemale,1,0);
    //end of vertical box for radio buttons
    topGrid->addItem(radioV, 7, 1);

    topGrid->addWidget(profilePic,6,0);
    topGrid->addWidget(browseButton,6,1);



    topGrid->addItem(new QSpacerItem(0,40),0,0);
    topGrid->addItem(new QSpacerItem(0,40),1,1);
    topGrid->addItem(new QSpacerItem(0,40),2,2);
    topGrid->addItem(new QSpacerItem(0,40),3,3);
    topGrid->addItem(new QSpacerItem(0,40),4,4);
    topGrid->addItem(new QSpacerItem(0,40),5,5);
    topGrid->addItem(new QSpacerItem(0,40),6,6);
    topGrid->addItem(new QSpacerItem(0,40),7,7);
    topGrid->addItem(new QSpacerItem(0,150),8,8);

    //end of top grid

    //combine all three main elements in vertical box
    mainV->addItem(topGrid);
    mainV->addWidget(submitButton);
    mainV->addWidget(backButton);
    mainV->addWidget(error);
    //mainV->addWidget(submitButton);

    setLayout(mainV);
    this->resize(this->width(), 30);
    QObject::connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(signUp()));
    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(goBack()));
    QObject::connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(browsePic()));


}

void signUpForm::browsePic()
{

    profilePicField->setText(
        QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen",
            "Images (*.png *.jpg *jpeg);;"));

}
void signUpForm::signUp()
{
    //check this for JSON interactions : https://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5
    //check if username exists - this must be unqiue

    this->error->setText(""); //empty text field if it was filled before
    QString error; //stores our errors to display to the user

    QString username = this->userNameField->text();
    if (username.isEmpty()) { error += "Fill in your username please\n"; }
    if (!checkUsername(username)) { error += "username already taken\n"; }

    QString fname = this->firstNameField->text();
    if (fname.isEmpty()) { error += "Fill in your first name please\n"; }
    QString lname = this->lastNameField->text();
    if (lname.isEmpty()) { error += "Fill in your last name please\n"; }

    QDate dateOfBirth = this->dateField->selectedDate();

    QString gender = "Unspecified";
    if (this->genderFieldMale->isChecked()){
        gender = "Male";
    }
    else if (this->genderFieldFemale->isChecked()){
        gender = "Female";
    }

    QString email = this->emailField->text();
    //validate email
    if (!validateEmail(email)) { error += "Please insert a valid email\n"; }

    //check password for requirements
    QRegExp passREX("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])[a-zA-Z0-9]{8,}$");
    passREX.setPatternSyntax(QRegExp::RegExp);

    QString password = this->passwordField->text();
    if ( (password == this->confirmPasswordField->text())
         && passREX.exactMatch(password)) {
    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Sha1);
    hash->addData(password.toUtf8());
    password = hash->result();
    }
    else {
      if ((password == this->confirmPasswordField->text())) {
       error += "Invalid password; password should consist of at least 8 characters and contain at\nleast one number, upper and lower case letters\n";
       }else{
       error += "passwords don't match";
      }
    }


    if(error.isEmpty()){
    //add new user to the users map in json file
        QString val;
        QFile file;
        file.setFileName("../gameOne/users.json");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        val = file.readAll();

        QJsonDocument doc;
        doc = QJsonDocument::fromJson(val.toUtf8());


        QString finalProfilePicture;
       if(profilePicField->text().isEmpty()) {
           finalProfilePicture = ":/static_images/default_pp.png";
       }
       else {

           QFileInfo profilePic(profilePicField->text());
           QString newPath = QDir::currentPath();

           newPath.append("/userProfilePic");
           if (!QDir(newPath).exists())
              { //create the folder if it doesn't exist
               QDir().mkdir(newPath);
           }
           newPath.append("/" + username+ "." + profilePic.suffix());

           //create a copy of the image for the profile pic
           if (QFile::exists(newPath)) //if a file in the same exists remove it
               { QFile::remove(newPath); }

           QFile::copy(profilePicField->text(), newPath);

           finalProfilePicture = newPath;
       }

       qDebug() << finalProfilePicture;



        //create new user json object
        QJsonObject newUser;
        newUser["first_name"] = fname;
        newUser["last_name"] = lname;
        newUser["birthdate"] = dateOfBirth.toString();
        newUser["email"] = email;
        newUser["gender"] = gender;
        newUser["username"] = username;
        newUser["password"] = password;
        newUser["profile_picture"] = finalProfilePicture;
        newUser["current_score"] = 0;
        newUser["high_score"] = 0;


        QJsonObject RootObject = doc.object();
        QJsonObject usersObject = RootObject["users"].toObject();

        //update JSON
        usersObject.insert(username,newUser);
        RootObject["users"] = usersObject;
        doc.setObject(RootObject);
        file.resize(0);
        file.write(doc.toJson());
        file.close();

        //create a user object and pass it to the welcome page
         user* activeUser;
         activeUser = new user(
                     fname,
                     lname,
                     username,
                     password,
                     dateOfBirth.toString(),
                     gender,
                     email,
                     finalProfilePicture);

        welcomePage *window1 = new welcomePage(activeUser);
        window1->show();
        this->close();


    }else
    {
    this->error->setText(error);
    this->error->setVisible(true);
    }
};

bool signUpForm::validateEmail(QString email){
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    return mailREX.exactMatch(email);
}

bool signUpForm::checkUsername(QString username){
    //return True if Username is unique else returns false
    QString val;
    QFile file;
    file.setFileName("../gameOne/users.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument doc;
    doc = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject jObj = doc.object();
    jObj = jObj["users"].toObject();
    if (jObj.keys().contains(username)){
        return false;
    }
    return true;
}

void signUpForm::goBack(){
    loginPage *window1 = new loginPage;
    window1->show();
    this->close();
}
