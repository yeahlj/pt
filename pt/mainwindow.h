#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void cutImage();//将图片分割成一个一个小方块

        void Random();// 打乱

        void moveImage();//图片移动

        void mousePressEvent (QMouseEvent *event);//鼠标单击事件
        int taskFinish();//判断拼图是否完成

        void sumPoint();// 拼图完成后计算分数

        int sumSteps;//定义储存总步数的变量

        QTimer *timer;// 定时器

    private slots://以下都是一些和信号绑定的槽函数

        void on_btn_clicked();// 新建按钮触发的槽函数
        void onTimerOut ();//定时器溢出槽函数

        void on_pushButton_clicked();//退出按钮触发的槽函数
        void on_pushButton_2_clicked();// 重来按钮触发的槽函数
        /*void on_action_N_triggered();// 菜单中新建的槽函数
        void on_action_R_triggered();//菜单中重来的槽函数
        void on_action_E_triggered();//菜单中退出的槽函数
        void on_action_3_triggered();// 菜单中初级的槽函数
        void on_action_4_triggered() ;//菜单中中级的槽函数
        void on_action_5_triggered();//菜单中高级的槽函数
*/
        private:
        Ui::MainWindow *ui;

        QString strFileName;// 文件名称

        QImage* pSourceImage;//原图

        QLabel* pLbImage[36];// 存储最多36个label,代码中需要将pImage [x] [y]的图片设置到相应的label上

        QImage pImage [6][6]; // 存储最多36张小图片

        int pCompare[6][6]; //标记数组;

    protected:

        void keyPressEvent (QKeyEvent *event);
};
#endif // MAINWINDOW_H
