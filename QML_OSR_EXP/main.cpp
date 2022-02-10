#include <QApplication>
//#include <QWebView>
#include "QmlOSRExpMainWindow.h"
#include "WidgetOSRItem.h"
#include <QListView>
#include <QStandardItemModel>
#include <QQuickWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QString>



void WaittingClose(QmlOSRExpMainWindow* w)
{
    QEventLoop loop;
    QObject::connect(w, &QmlOSRExpMainWindow::	visibleChanged,[&loop](bool s)
    {
        if(!s)
            loop.exit(0);
    });
    loop.exec();
}

void showWebViewExample()
{
    //////////////exp
    /// 嵌入qwebview
    ///

//    QmlOSRExpMainWindow w_WebViewExp;
//    w_WebViewExp.setTitle("WebViewExp");
//    w_WebViewExp.show();
//    w_WebViewExp.load(QUrl("qrc:/QML_RSR_EXP.qml"));


//    //新建一个QWebView放入qml osr item中 . 支持https需要在程序目录放入相关dll
//    QWebView osrWebView;
//    osrWebView.setUrl(QUrl("https://www.csdn.net/"));
//    w_WebViewExp.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(&osrWebView));


//    WaittingClose(&w_WebViewExp);
}

void showListViewExample()
{
    //////////////exp2
    /// 嵌入qlistview
    ///


    QmlOSRExpMainWindow w_ListViewExp;
    w_ListViewExp.setTitle("ListViewExp");
    w_ListViewExp.show();
    w_ListViewExp.load(QUrl("qrc:/QML_RSR_EXP.qml"));


    //新建一个QWebView放入qml osr item中 . 支持https需要在程序目录放入相关dll
    QListView osrListView;

    QStandardItemModel* model = new QStandardItemModel(&osrListView);
    for(int i = 0; i < 100; i++)
    {
        QStandardItem* item = new QStandardItem(QString("item %1").arg(i+1));
        model->appendRow(item);
    }
    osrListView.setModel(model);

    w_ListViewExp.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(&osrListView));



    WaittingClose(&w_ListViewExp);
}

void showTextEidtExample()
{
	//////////////exp2
	/// 嵌入qtextedit
	///


	QmlOSRExpMainWindow w_TextEditExp;
	w_TextEditExp.setTitle("TextEditExp");
	w_TextEditExp.show();
	w_TextEditExp.load(QUrl("qrc:/QML_RSR_EXP.qml"));


	//新建一个QTextEidt放入OSRItem
	QTextEdit textEdit;
	textEdit.setText("QTextEidt");

	w_TextEditExp.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(&textEdit));


	WaittingClose(&w_TextEditExp);
}


void showPushButtonExample()
{
	//////////////exp2
	/// 嵌入pushbutton
	///


	QmlOSRExpMainWindow w_PushButtonExp;
	w_PushButtonExp.setTitle("PushButtonExp");
	w_PushButtonExp.show();
	w_PushButtonExp.load(QUrl("qrc:/QML_RSR_EXP.qml"));


	//新建一个QTextEidt放入OSRItem
	QWidget pannel;
	QPushButton *btn1 = new QPushButton(QStringLiteral("测试按钮1"));
	QPushButton *btn2 = new QPushButton(QStringLiteral("测试按钮2"));
	QPushButton *btn3 = new QPushButton(QStringLiteral("测试按钮3"));
	QPushButton *btn4 = new QPushButton(QStringLiteral("测试按钮4"));

	btn1->setParent(&pannel);
	btn2->setParent(&pannel);
	btn3->setParent(&pannel);
	btn4->setParent(&pannel);

	QObject::connect(btn1, &QPushButton::clicked, [&btn1](){
		QString btnText = btn1->text();
		QString text = QStringLiteral("按钮'%1'被点击");
		text = text.arg(btnText);
		QMessageBox::information(0,QStringLiteral("提示"), text);
	});

	QObject::connect(btn2, &QPushButton::clicked, [&btn2](){
		QString btnText = btn2->text();
		QString text = QStringLiteral("按钮'%1'被点击");
		text = text.arg(btnText);
		QMessageBox::information(0,QStringLiteral("提示"), text);
	});

	QObject::connect(btn3, &QPushButton::clicked, [&btn3](){
		QString btnText = btn3->text();
		QString text = QStringLiteral("按钮'%1'被点击");
		text = text.arg(btnText);
		QMessageBox::information(0,QStringLiteral("提示"), text);
	});

	QObject::connect(btn4, &QPushButton::clicked, [&btn4](){
		QString btnText = btn4->text();
		QString text = QStringLiteral("按钮'%1'被点击");
		text = text.arg(btnText);
		QMessageBox::information(0,QStringLiteral("提示"), text);
	});

	QVBoxLayout* vbLayout = new QVBoxLayout(&pannel);
	vbLayout->addWidget(btn1);
	vbLayout->addWidget(btn2);
	vbLayout->addWidget(btn3);
	vbLayout->addWidget(btn4);
	vbLayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding));

	w_PushButtonExp.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(&pannel));

	WaittingClose(&w_PushButtonExp);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, true);

    //register diy qml tools
    qmlRegisterType<WidgetOSRItem>("Diy.WidgetOSRItem",1,0, "WidgetOSRItem");

    QWidget testView;
    testView.setWindowTitle(QStringLiteral("测试"));
    QPushButton *btn1 = new QPushButton(QStringLiteral("测试QWebView"));
    QPushButton *btn2 = new QPushButton(QStringLiteral("测试QListView"));
    QPushButton *btn3 = new QPushButton(QStringLiteral("测试QTextEdit"));
    QPushButton *btn4 = new QPushButton(QStringLiteral("测试QPushButton"));

    btn1->setParent(&testView);
    btn2->setParent(&testView);
    btn3->setParent(&testView);
    btn4->setParent(&testView);

    QVBoxLayout* vbLayout = new QVBoxLayout(&testView);
    vbLayout->addWidget(btn1);
    vbLayout->addWidget(btn2);
    vbLayout->addWidget(btn3);
    vbLayout->addWidget(btn4);
    vbLayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding));

    QObject::connect(btn1, &QPushButton::clicked, [](){
        showWebViewExample();
    });

    QObject::connect(btn2, &QPushButton::clicked, [](){
        showListViewExample();
    });

    QObject::connect(btn3, &QPushButton::clicked, [](){
        showTextEidtExample();
    });

    QObject::connect(btn4, &QPushButton::clicked, [](){
        showPushButtonExample();
    });


    testView.show();


    int res =  a.exec();
    return res;
}
