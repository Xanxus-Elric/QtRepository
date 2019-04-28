#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //set the Title of the Main Widget
    this->setWindowTitle("Contacter");

    //Add the Prompt Label
    QLabel *NamePrompt = new QLabel("Name", this);
    QLabel *AddressPrompt = new QLabel("Address", this);

    //Add the Show Frame(LineEdit and TextEdit), there are read-only
    this->NameEdit = new QLineEdit(this);
    this->AddressEdit = new QTextEdit(this);

    this->NameEdit->setReadOnly(true);
    this->AddressEdit->setReadOnly(true);

    //Add the Some Necessary Button
    this->AddBtn = new QPushButton("Add", this);
    this->DelBtn = new QPushButton("Del", this);
    this->ModifyBtn = new QPushButton("Modify", this);
    this->SearchBtn = new QPushButton("Search", this);

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

    QGridLayout *MainLayout = new QGridLayout(this);
    MainLayout->addLayout(InfoLayout, 0, 0);
    MainLayout->addLayout(BtnLayout, 0, 1);

    //Initialize the Sub Form
    this->AddForm = new AddDialog(this);
    this->ModifyForm = new ModifyDialog(this);
    this->SearchForm = new SearchDialog(this);

    //Read the AddressBook.Txt File to Get the Information
    this->LoadFile();

    //connect the Handle
    connect(this->AddBtn, SIGNAL(clicked(bool)), this, SLOT(AddHandle()));
    connect(this->AddForm, SIGNAL(AddFinishSignal()), this, SLOT(GetAddInfo()));

    connect(this->ModifyBtn, SIGNAL(clicked(bool)), this, SLOT(ModifyHandle()));
    connect(this->ModifyForm, SIGNAL(ModifyFinishSignal()), this, SLOT(GetModifyInfo()));

}

void MainWidget::LoadFile(){
    //Open the File to read the Contacter's Information from
    this->MapFile = new QFile("AddressBook.txt");

    if (!this->MapFile->exists()){
        //Create a Txt File
        this->MapFile->open(QIODevice::ReadWrite | QIODevice::Text);
    }
    else{
        if (this->MapFile->open(QIODevice::ReadOnly)){
            qDebug() << "Open File Success";
        }
        else{
            qDebug() << "Open File Fail";
            return ;
        }
    }

    //Store the Information on the File to QMap
    QTextStream In(this->MapFile);
    QString TempStr;
    QStringList TempStrList;

    this->InfoMap.clear();

    while(!In.atEnd()){
        TempStr = In.readLine();
        TempStrList = TempStr.split(",", QString::KeepEmptyParts);
        if (TempStrList.isEmpty()){
            return ;
        }
        else{
            //Store the Information to the QMap
            this->InfoMap.insert(TempStrList[0], TempStrList[1]);
            qDebug() << TempStrList[0] << " : " << TempStrList[1];
        }
    }

    this->NameEdit->setText(TempStrList[0]);
    this->AddressEdit->setText(TempStrList[1]);

    this->MapFile->close();
}

//void MainWidget::CloseEvent(QCloseEvent *event){
//    this->SaveFile();
//}

void MainWidget::SaveFile(){
    //Open the File to Save the Contacter's Information to
    this->MapFile->open(QIODevice::WriteOnly);

    //Store the Information on the QMap to the File
    QTextStream Out(this->MapFile);
    QMapIterator<QString, QString> MapIter(this->InfoMap);

    while(MapIter.hasNext()){
        MapIter.next();
        qDebug() << MapIter.key() << " : " << MapIter.value();
        Out << MapIter.key() << "," << MapIter.value() << endl;
    }

    this->MapFile->close();
}

void MainWidget::AddHandle(){
    this->AddForm->exec();
}

void MainWidget::GetAddInfo(){
    QString Name = this->AddForm->GetName();
    QString Address = this->AddForm->GetAddress();

    //Show the New contacter's Information on the MainWidget
    this->NameEdit->setText(Name);
    this->AddressEdit->setText(Address);

    if (this->InfoMap.contains(Name)){
        int Ret = QMessageBox::warning(this,
                                     "Add Contacter Warning",
                                     "The Contacter already exists",
                                     QMessageBox::Ok,
                                     QMessageBox::Cancel);

        if (Ret == QMessageBox::Cancel){
            return ;
        }
    }

    //Add the New Contacter's Information to the QMap
    this->InfoMap.insert(Name, Address);
}

void MainWidget::DelHandle(){
    QMapIterator<QString, QString> MapIter(this->InfoMap);

    while(MapIter.hasNext()){
        MapIter.next();
        if (MapIter.key() == this->NameEdit->text()){
            break;
        }
    }

    MapIter.next();
    this->InfoMap.remove(this->NameEdit->text());

    this->NameEdit->setText(MapIter.key());
    this->
}

void MainWidget::ModifyHandle(){
    //Delete the Current Contacter's Information from QMap

    //Initialize the Show String on the ModifyForm
    this->ModifyForm->SetName(this->NameEdit->text());
    this->ModifyForm->SetAddress(this->AddressEdit->toPlainText());
    this->ModifyForm->exec();
}

void MainWidget::GetModifyInfo(){
    //Show the contacter's Information after Modification on the MainWidget
    this->NameEdit->setText(this->ModifyForm->GetName());
    this->AddressEdit->setText(this->ModifyForm->GetAddress());

    //Add the Contacter's Information after Modification to the QMap

}

void MainWidget::SearchHandle(){
    this->SearchForm->exec();
}

void MainWidget::GetSearchInfo(){
    //Get the Name Of Contacter which does user want to search
    QString ContactName = this->SearchForm->GetSearchName();
    //Find in the QMap
    //.....
}

MainWidget::~MainWidget()
{
    this->SaveFile();

}
