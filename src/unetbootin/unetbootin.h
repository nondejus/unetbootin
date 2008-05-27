#ifndef UNETBOOTIN_H
#define UNETBOOTIN_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#include "ui_unetbootin.h"

#ifdef Q_OS_WIN32
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <shellapi.h>
#endif

#ifdef AUTOSUPERGRUBDISK
#define UNETBOOTINB "Auto Super Grub Disk"
#else
#define UNETBOOTINB "UNetbootin"
#endif

class callexternappT : public QThread
{
public:
	QString execFile;
	QString execParm;
	QString retnValu;
	void run();
};

class unetbootin : public QWidget, private Ui::unetbootinui
{
	Q_OBJECT

public:
	unetbootin(QWidget *parent = 0);
	QString appDir;
	QString appLoc;
	QString ubntmpf;
	QString nameDistro;
	QString nameVersion;
	bool isarch64;
	bool islivecd;
	bool isnetinstall;
	QString targetDrive;
	QString targetPath;
	QString installType;
	QString targetDev;
	QString rawtargetDev;
	QString devuuid;
	QString postinstmsg;
	QString sourcefile, destinfile;
	QString kernelLine, kernelParam, kernelLoc, kernelOpts, initrdLine, initrdLoc, initrdOpts;
	QString sevzcommand;
	#ifdef Q_OS_UNIX
	QString fdiskcommand;
	QString sfdiskcommand;
	QString volidcommand;
	QString syslinuxcommand;
	#endif
	QPair<QPair<QStringList, QStringList>, QStringList> listarchiveconts(QString archivefile);
	bool extractfile(QString filepath, QString destinfile, QString archivefile);
	bool extractkernel(QString archivefile, QString kernoutputfile, QStringList archivefileconts);
	bool extractinitrd(QString archivefile, QString initoutputfile, QStringList archivefileconts);
	QString extractcfg(QString archivefile, QStringList archivefileconts);
	void extractiso(QString isofile, QString exoutputdir);
	QStringList makepathtree(QString dirmkpathw, QStringList pathlist);
	QStringList extractallfiles(QString archivefile, QString dirxfilesto, QPair<QStringList, QStringList> filesizelist);
	QString getcfgkernargs(QString cfgfile);
	void downloadfile(QString fileurl, QString targetfile);
	QString downloadpagecontents(QString pageurl);
	void sysreboot();
	QString callexternapp(QString xexecFile, QString xexecParm);
	QString getuuid(QString voldrive);
	#ifdef Q_OS_UNIX
	QString locatecommand(QString commandtolocate, QString reqforinstallmode, QString packagename);
	QString locatedevicenode(QString mountpoint);
	QString locatemountpoint(QString devicenode);
	QString getGrubNotation(QString devicenode);
	int letterToNumber(QChar lettertoconvert);
	int getDiskNumber(QString devicenode);
	int getPartitionNumber(QString devicenode);
	#endif
	#ifdef Q_OS_WIN32
	void installsvzip();
	void configsysEdit();
	void bootiniEdit();
	void vistabcdEdit();
	#endif
	void instIndvfl(QString srcfName, QString dstfName);
	void runinst();
	void instDetType();
	void runinsthdd();
	void runinstusb();
	void fininstall();

private slots:
	void on_distroselect_currentIndexChanged(int distroselectIndex);
	void on_typeselect_currentIndexChanged(int typeselectIndex);
	void on_dverselect_currentIndexChanged();
	void on_diskimagetypeselect_currentIndexChanged();
	void on_FloppyFileSelector_clicked();
	void on_KernelFileSelector_clicked();
	void on_InitrdFileSelector_clicked();
	void on_CfgFileSelector_clicked();
	void on_cancelbutton_clicked();
	void on_okbutton_clicked();
	void on_frebootbutton_clicked();
	void on_fexitbutton_clicked();

public slots:
	void dlprogressupdate(int dlbytes, int maxbytes);
	void dlprogressupdate64(qint64 dlbytes, qint64 maxbytes);
};

#endif

