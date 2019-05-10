#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //set the Title of the Main Widget
    this->setWindowTitle("Contacter");

    //Add the Prompt Label
    QLabel *NamePrompt      = new QLabel("Name", this);
    QLabel *AddressPrompt   = new QLabel("Address", this);

    //Add the Show Frame(LineEdit and TextEdit), there are read-only
    this->NameEdit      = new QLineEdit(this);
    this->AddressEdit   = new QTextEdit(this);

    this->NameEdit->setReadOnly(true);
    this->AddressEdit->setReadOnly(true);

    //Add the Some Necessary Button
    this->AddBtn        = new QPushButton("Add", this);
    this->DelBtn        = new QPushButton("Del", this);
    this->ModifyBtn     = new QPushButton("Modify", this);
    this->SearchBtn     = new QPushButton("Search", this);
    this->PrevBtn       = new QPushButton("Previous", this);
    this->NextBtn       = new QPushButton("Next", this);
    this->DelBtn->setEnabled(false);
    this->ModifyBtn->setEnabled(false);
    this->SearchBtn->setEnabled(false);
    this->PrevBtn->setEnabled(false);
    this->NextBtn->setEnabled(false);

    //Set the Layout Of All the Widget
    QVBoxLayout *BtnLayout = new QVBoxLayout();
    BtnLayout->addWidget(this->AddBtn);
    BtnLayout->addWidget(this->DelBtn);
    BtnLayout->addWidget(this->ModifyBtn);
    BtnLayout->addWidget(this->SearchBtn);

    QVBoxLayout *InfoLayout = new QVBoxLayout();
    InfoLayout->addWidget(NamePrompt);        
    InfoLayout->addWidget(this->NameEdit);
    InfoLayout->addWidget(AddressPrompt);
    InfoLayout->addWidget(this->AddressEdit);

    QHBoxLayout *PNLayout = new QHBoxLayout();
    PNLayout->addWidget(this->PrevBtn);
    PNLayout->addWidget(this->NextBtn);

    InfoLayout->addLayout(PNLayout);

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addLayout(InfoLayout, 0, 0);
    MainLayout->addLayout(BtnLayout, 0, 1);

    //Initialize the Sub Form Dialog
    this->AddForm       = new AddDialog(this);
    this->ModifyForm    = new ModifyDialog(this);
    this->SearchForm    = new SearchDialog(this);

    this->setMaximumSize(400, 300);
    this->setMinimumSize(400, 300);

    //Read the AddressBook.Txt File to Get the Information
    this->LoadFile();

    //connect the Handle
    connect(this->AddBtn, SIGNAL(clicked(bool)), this, SLOT(AddHandle()));
    connect(this->AddForm, SIGNAL(AddFinishSignal()), this, SLOT(GetAddInfo()));

    connect(this->DelBtn, SIGNAL(clicked(bool)), this, SLOT(DelHandle()));

    connect(this->ModifyBtn, SIGNAL(clicked(bool)), this, SLOT(ModifyHandle()));
    connect(this->ModifyForm, SIGNAL(ModifyFinishSignal()), this, SLOT(GetModifyInfo()));

    connect(this->SearchBtn, SIGNAL(clicked(bool)), this, SLOT(SearchHandle()));
    connect(this->SearchForm, SIGNAL(SearchFinishSignal()), this, SLOT(GetSearchInfo()));

    connect(this->PrevBtn, SIGNAL(clicked(bool)), this, SLOT(PrevHandle()));
    connect(this->NextBtn, SIGNAL(clicked(bool)), this, SLOT(NextHandle()));
}

void MainWidget::LoadFile(){
    //Create the File "AddressBook.txt" to save the Message
    this->MapFile = new QFile("AddressBook.txt");

    //Judge whether this file has been existed
    if (!this->MapFile->open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug() << "Open File Fail";
        return ;
    }

    //Create the Input Stream to Read Message From the File
    QTextStream In(this->MapFile);
    QString TempStr;
    QStringList TempStrList;

    //transfer the Message to the Map Container Line By Line
    while(!In.atEnd()){
        TempStr = In.readLine();

        TempStrList = TempStr.split(",");
        if (TempStrList.isEmpty()){
            qDebug() << "The Store File may be error";
            return ;
        }
        else{
            //Store the Information to the QMap
            this->InfoMap.insert(TempStrList[0], TempStrList[1]);
        }
    }

    if (!this->InfoMap.empty()){
        this->NameEdit->setText(this->InfoMap.firstKey());
        this->AddressEdit->setText(this->InfoMap.first());

        this->DelBtn->setEnabled(true);
        this->ModifyBtn->setEnabled(true);

        if (this->InfoMap.size() >= 2){
            this->NextBtn->setEnabled(true);
            this->SearchBtn->setEnabled(true);
        }
    }

    //Close the File
    this->MapFile->close();
}

void MainWidget::SaveFile(){
    //Open the File to Save the Contacter's Information to
    this->MapFile->open(QIODevice::WriteOnly);

    //Create the Output Stream to Store the Message
    QTextStream Out(this->MapFile);
    QMapIterator<QString, QString> MapIter(this->InfoMap);

    //traverse the Map Container, Store each member to the File
    while(MapIter.hasNext()){
        MapIter.next();
        Out << MapIter.key() << "," << MapIter.value() << endl;
    }

    this->MapFile->close();
}

void MainWidget::AddHandle(){
    //Create the Add Form, and wait for the User's Operation
    this->AddForm->exec();
}

void MainWidget::GetAddInfo(){
    //Firstly, Get the Message From the AddForm
    QString Name = this->AddForm->GetName();
    QString Address = this->AddForm->GetAddress();

    //Judge if the Contacter has been existed
    if (this->InfoMap.contains(Name)){
        int Ret = QMessageBox::warning(this,
                                       "Add Contacter Warning",
                                       "The Contacter Already Existed",
                                       QMessageBox::Ok,
                                       QMessageBox::Cancel);

        if (Ret == QMessageBox::Cancel){
            return ;
        }
    }

    //Continue to Add this Contacter, For Map Container, It just will change the Value.
    this->InfoMap.insert(Name, Address);
    //Show the New Contacter On the Main Form
    this->NameEdit->setText(Name);
    this->AddressEdit->setText(Address);

    //enable other buttons
    this->DelBtn->setEnabled(true);
    this->ModifyBtn->setEnabled(true);
    this->SearchBtn->setEnabled(true);
}

void MainWidget::DelHandle(){
    if (this->InfoMap.empty()){
        return ;
    }

    QString DelName = this->NameEdit->text();

    if (!this->PrevBtn->isEnabled()){
        //the Current show is the first on the list
        //Show the Next, and remove the First one
        QMapIterator<QString, QString> MapIter(this->InfoMap);
        MapIter.next();     //Let it point to the First Member;

        if (MapIter.hasNext()){
            MapIter.next();

            this->NameEdit->setText(MapIter.key());
            this->AddressEdit->setText(MapIter.value());
        }
        else{
            this->NameEdit->clear();
            this->AddressEdit->clear();
        }
    }
    else if (!this->NextBtn->isEnabled()){
        QMapIterator<QString, QString> MapIter(this->InfoMap);
        MapIter.toBack();
        MapIter.previous();     //Let it Point to the Last Member

        if (MapIter.hasPrevious()){
            MapIter.previous();

            this->NameEdit->setText(MapIter.key());
            this->AddressEdit->setText(MapIter.value());
        }
        else{
            this->NameEdit->clear();
            this->AddressEdit->clear();
        }
    }
    else{
        QMapIterator<QString, QString> MapIter(this->InfoMap);

        while(MapIter.hasNext()){
            MapIter.next();
            if (MapIter.key() == this->NameEdit->text()){
                break;
            }
        }

        if (MapIter.hasNext()){
            MapIter.next();
            this->NameEdit->setText(MapIter.key());
            this->AddressEdit->setText(MapIter.value());
        }
        else{
            //Check The size of the Map List
            if (!this->InfoMap.empty()){
                MapIter = this->InfoMap;
                MapIter.toBack();
                MapIter.previous();
                MapIter.previous();
                this->NameEdit->setText(MapIter.key());
                this->AddressEdit->setText(MapIter.value());
            }
        }
    }

    this->InfoMap.remove(DelName);

    qDebug() << "Size of this Map" << this->InfoMap.size();

    if (this->InfoMap.size() == 1){
        //Disable the PrevBtn and NextBtn
        this->PrevBtn->setEnabled(false);
        this->NextBtn->setEnabled(false);
    }
    else if (this->InfoMap.size() == 0){
        this->DelBtn->setEnabled(false);
        this->ModifyBtn->setEnabled(false);
        this->SearchBtn->setEnabled(false);
        this->NameEdit->clear();
        this->AddressEdit->clear();
    }
}

void MainWidget::ModifyHandle(){
    //Delete the Current Contacter's Information from QMap

    //Initialize the Show String on the ModifyForm
    this->ModifyForm->SetName(this->NameEdit->text());
    this->ModifyForm->SetAddress(this->AddressEdit->toPlainText());
    this->ModifyForm->exec();
}

void MainWidget::GetModifyInfo(){
    QString ModifyKey   = this->NameEdit->text();
    QString NewKey      = this->ModifyForm->GetName();
    QString NewValue    = this->ModifyForm->GetAddress();

    qDebug() << "the Modify key is " << ModifyKey;

    //remove the previous member
    this->InfoMap.remove(ModifyKey);

    //Show the contacter's Information after Modification on the MainWidget
    this->NameEdit->setText(NewKey);
    this->AddressEdit->setText(NewValue);

    //Add new member to key
    this->InfoMap.insert(NewKey, NewValue);
}

void MainWidget::SearchHandle(){
    this->SearchForm->exec();
}

void MainWidget::GetSearchInfo(){
    //Get the Name Of Contacter which does user want to search
    QString ContactName = this->SearchForm->GetSearchName();

    //Find in the QMap
    if (this->InfoMap.contains(ContactName)){
        this->NameEdit->setText(ContactName);
        this->AddressEdit->setText(this->InfoMap.value(ContactName));
        this->SearchForm->close();
    }
    else{
        int Ret = QMessageBox::information(this,
                                         "No Contact Found!",
                                         "You can change Name, and Search again",
                                         "Try Again", "Cancel");

        if (Ret == 1){
            this->SearchForm->close();
        }
    }
}

void MainWidget::PrevHandle(){
    //First, Judge if the InfoMap is empty or not
    if (this->InfoMap.empty() ||
        this->NameEdit->text().isEmpty() ||
        this->AddressEdit->toPlainText().isEmpty()){
        return ;
    }

    QMapIterator<QString, QString> TempIter(this->InfoMap);
    TempIter.toBack();

    //First, Let the Iterator point to correct position
    //For TempIter point to header, so use HasNext
    while(TempIter.hasPrevious()){
        TempIter.previous();
        if (TempIter.key() == this->NameEdit->text()){
            break;
        }
    }

    if (TempIter.hasPrevious()){
        //Show the prevoius Information on the MainForm
        qDebug() << "Before " << TempIter.key() << TempIter.value();

        TempIter.previous();

        qDebug() << "After " << TempIter.key() << TempIter.value();

        this->NameEdit->setText(TempIter.key());
        this->AddressEdit->setText(TempIter.value());

        //Judge again
        if (!TempIter.hasPrevious()){
            this->PrevBtn->setEnabled(false);
        }
        else{
            this->PrevBtn->setEnabled(true);
        }

        if (!TempIter.hasNext()){
            this->NextBtn->setEnabled(false);
        }
        else{
            this->NextBtn->setEnabled(true);
        }
    }
}

void MainWidget::NextHandle(){
    //First, Judge if the InfoMap is empty or not
    if (this->InfoMap.empty() ||
        this->NameEdit->text().isEmpty() ||
        this->AddressEdit->toPlainText().isEmpty()){
        return ;
    }

    QMapIterator<QString, QString> TempIter(this->InfoMap);

    //First, Let the Iterator point to correct position
    while(TempIter.hasNext()){
        TempIter.next();
        if (TempIter.key() == this->NameEdit->text()){
            break;
        }
        qDebug() << "Current Temp " << TempIter.key() << TempIter.value();
    }

    if (TempIter.hasNext()){
        TempIter.next();
        this->NameEdit->setText(TempIter.key());
        this->AddressEdit->setText(TempIter.value());

        if (!TempIter.hasNext()){
            this->NextBtn->setEnabled(false);
        }
        else{
            this->NextBtn->setEnabled(true);
        }

        if (!TempIter.hasPrevious()){
            this->PrevBtn->setEnabled(false);
        }
        else{
            this->PrevBtn->setEnabled(true);
        }
    }
}

MainWidget::~MainWidget()
{
    this->SaveFile();

}
