/*
 * Author : dimos katsimardos
 * Date   : 2019, August 16
 * Update I : Add functionality for audio & video converting
 *            using the well known Linux command ffmpeg
 */
#include "youtubedl.h"
#include "ui_youtubedl.h"

YoutubeDl::YoutubeDl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YoutubeDl)
{
    ui->setupUi(this);
    setPixmaps();
}

YoutubeDl::~YoutubeDl()
{
    delete ui;
}

void YoutubeDl::setPixmaps()
{
    QPixmap audio(":/audio.png");
    QPixmap video(":/video.png");
    ui->audio_label->setPixmap(audio.scaled(ui->audio_label->width(), ui->audio_label->height(), Qt::KeepAspectRatio));
    ui->video_label->setPixmap(video.scaled(ui->video_label->width(), ui->video_label->height(), Qt::KeepAspectRatio));
}

QString YoutubeDl::getDir() const
{
    return dir;
}

void YoutubeDl::setDir(const QString &value)
{
    dir = value;
}

// Check if a directory really exists in the system
// using QDir Qt's class functionality
bool YoutubeDl::check_if_dir_is_valid(QString &dir_name)
{
    return QDir(dir_name).exists() ? true : false;
}

QString YoutubeDl::getUrl() const
{
    return url;
}

void YoutubeDl::setUrl(const QString &value)
{
    url = value;
}

QString YoutubeDl::getUrl_format() const
{
    return url_format;
}

void YoutubeDl::setUrl_format(const QString &value)
{
    url_format = value;
}

QString YoutubeDl::getUrl_title() const
{
    return url_title;
}

void YoutubeDl::setUrl_title(const QString &value)
{
    url_title = value;
}

QString YoutubeDl::getNew_filename() const
{
    return new_filename;
}

void YoutubeDl::setNew_filename(const QString &value)
{
    new_filename = value;
}

QString YoutubeDl::getFormat() const
{
    return format;
}

void YoutubeDl::setFormat(const QString &value)
{
    format = value;
}

QString YoutubeDl::getFilename() const
{
    return filename;
}

void YoutubeDl::setFilename(const QString &value)
{
    filename = value;
}

QString YoutubeDl::getChannels() const
{
    return channels;
}

void YoutubeDl::setChannels(const QString &value)
{
    channels = value;
}

QString YoutubeDl::getBit_rate() const
{
    return bit_rate;
}

void YoutubeDl::setBit_rate(const QString &value)
{
    bit_rate = value;
}

QString YoutubeDl::getSample_rate() const
{
    return sample_rate;
}

void YoutubeDl::setSample_rate(const QString &value)
{
    sample_rate = value;
}

void YoutubeDl::on_confirm_button_clicked()
{
    int checked_action = QMessageBox::question(this, "Confirm", "Are you sure you wish to proceed?", QMessageBox::No | QMessageBox::Yes);
    if(checked_action==QMessageBox::No)
    {
        return;
    }

    QString pre_check = ui->dir_lineEdit->text();
    if(ui->url_lineEdit->text().isEmpty() || ui->dir_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "ERROR", "Url and directory should be both specified!");
        return;
    }
    if(check_if_dir_is_valid(pre_check)==false)
    {
        QMessageBox::warning(this, "ERROR", "The directory " + pre_check + " does not exist. Please provide a valid one and try again!");
        return;
    }
    setUrl(ui->url_lineEdit->text());
    setDir(ui->dir_lineEdit->text());
    QString message("URL: " + url + "\nPATH: " + dir + "\nProceeding..");
    QMessageBox::information(this, "INFO", message);
}

// Open File explorer in order to select a directory for the url to be saved
void YoutubeDl::on_explore_directory_radioButton_clicked()
{
    QString home_dir = "/home/" + qgetenv("USER");
    QString SelDirDialog = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                                      home_dir, QFileDialog::ShowDirsOnly
                                                                      | QFileDialog::DontResolveSymlinks);
    setDir(SelDirDialog);
    ui->dir_lineEdit->setText(SelDirDialog);
    // Next uncheck the radio button, since directory is selected
    ui->explore_directory_radioButton->setAutoExclusive(false);
    ui->explore_directory_radioButton->setChecked(false);
    ui->explore_directory_radioButton->setAutoExclusive(true);
}

// Do the same but with the Open Folder action on top of the toolbar
void YoutubeDl::on_open_folder_action_triggered()
{
    QString home_dir = "/home/" + qgetenv("USER");
    QString SelDirDialog = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                                      home_dir, QFileDialog::ShowDirsOnly
                                                                      | QFileDialog::DontResolveSymlinks);
    setDir(SelDirDialog);
    ui->dir_lineEdit->setText(SelDirDialog);
}

// Clear url and dir line Edits
void YoutubeDl::clear_fields()
{
    ui->clear_fields_radioButton->setAutoExclusive(false);
    ui->clear_fields_radioButton->setChecked(false);
    ui->clear_fields_radioButton->setAutoExclusive(true);
}

void YoutubeDl::on_clear_fields_radioButton_clicked()
{
    ui->url_lineEdit->setText("");
    ui->dir_lineEdit->setText("");
    // Wait 1 second
    // Next uncheck the radio button, since clear action is done
    QTimer::singleShot( 1000, this, SLOT(clear_fields()) );
}

// Find the url title and then print it
bool YoutubeDl::find_url_title()
{
    QProcess title_proc;
    title_proc.start("youtube-dl --get-filename " + url);
    if(!title_proc.waitForFinished(5000) || title_proc.exitStatus()!=0)
    {
        url_title = "[]";
        return false;
    }

    url_title = title_proc.readAllStandardOutput();
    url_title.remove("\n");

    return true;
}

void YoutubeDl::on_print_url_title_radioButton_clicked(bool checked)
{
    setUrl(ui->url_lineEdit->text());
    if(url.isEmpty())
    {
        QMessageBox::warning(this, "ERROR", "Please enter url and try again!");
        return;
    }

    if(checked)
    {
        if(find_url_title()==true)
        {
            QMessageBox::information(this, "URL TITLE", url_title);
        } else
        {
            QMessageBox::warning(this, "ERROR", "Could not find the url title!");
        }
    }
    // Uncheck the radio button now
    ui->print_url_title_radioButton->setAutoExclusive(false);
    ui->print_url_title_radioButton->setChecked(false);
    ui->print_url_title_radioButton->setAutoExclusive(true);
}

// Find the format and then print it
bool YoutubeDl::find_url_format()
{
    QProcess format_proc;
    format_proc.start("youtube-dl --get-format " + url);
    if(!format_proc.waitForFinished(7000) || format_proc.exitStatus()!=0)
    {
        url_format = "[]";
        return false;
    }

    url_format = format_proc.readAllStandardOutput();
    url_format.remove("\n");

    return true;
}

void YoutubeDl::on_print_url_format_radioButton_clicked(bool checked)
{
    if(url.isEmpty())
    {
        QMessageBox::warning(this, "ERROR", "Please enter url and try again!");
        return;
    }

    if(checked)
    {
        if(find_url_format()==true)
        {
            QMessageBox::information(this, "URL FORMAT", url_format);
        } else
        {
            QMessageBox::warning(this, "ERROR", "Could not find the url format!");
        }
    }
    // Uncheck the radio button now
    ui->print_url_format_radioButton->setAutoExclusive(false);
    ui->print_url_format_radioButton->setChecked(false);
    ui->print_url_format_radioButton->setAutoExclusive(true);
}

// Exit application if yes is entered
// A last prompt is appeared
void YoutubeDl::on_exit_button_clicked()
{
    int checked_action = QMessageBox::question(this, "Warning Message", "Are you sure you wish to exit the application?", QMessageBox::No | QMessageBox::Yes);

    if(checked_action==QMessageBox::Yes) {
        QApplication::quit();
    } else  if(checked_action==QMessageBox::No) {
        return;
    }
}

// YoutubeDl Utility Help Information
void YoutubeDl::on_information_button_clicked()
{
    QMessageBox::information(this, "INFORMATION", "This is a Youtube-dl GUI to download a url in audio or video format! Enter url, directory to save it, confirm your choices, choose format and press DOWNLOAD.");
}

// The Help action in the top bar
void YoutubeDl::on_information_action_triggered()
{
    QMessageBox::information(this, "Application Help", "This is a Youtube-dl GUI to download a url in audio or video format! Enter url, directory to save it, confirm your choices, choose format and press DOWNLOAD.");
}

// The exit application action in the top bar
void YoutubeDl::on_exit_application_action_triggered()
{
    int checked_action = QMessageBox::question(this, "Warning Message", "Are you sure you wish to exit the application?", QMessageBox::No | QMessageBox::Yes);

    if(checked_action==QMessageBox::Yes) {
        QApplication::quit();
    } else  if(checked_action==QMessageBox::No) {
        return;
    }
}

void YoutubeDl::on_about_app_action_triggered()
{
    QMessageBox::information(this, "ABOUT THE APP", "This is a custom Qt creator developed application for a url download that makes use of the Linux youtube-dl well known command. Have fun!");
}

void YoutubeDl::on_actionAbout_Youtube_dl_Utility_triggered()
{
    QMessageBox::information(this, "Youtube-dl Utility VERSION", "2019/08/16\nVersion 1.1.0");
}

void YoutubeDl::on_about_author_action_triggered()
{
    QMessageBox::information(this, "Author Information", "Dimosthenis Katsimardos\nwww.linkedin/com/in/dimkatsi91\nEurope, Greece");
}

// The youtube-dl actions to be triggered and run here
/* ================================================================================================================================================= */
void YoutubeDl::uncheck_radio_buttons()
{
    // Uncheck the audio_radioButton
    if(ui->audio_radioButton->isChecked())
    {
        ui->audio_radioButton->setAutoExclusive(false);
        ui->audio_radioButton->setChecked(false);
        ui->audio_radioButton->setAutoExclusive(true);
    }
    // Uncheck the video_radioButton
    if(ui->video_radioButton->isChecked())
    {
        ui->video_radioButton->setAutoExclusive(false);
        ui->video_radioButton->setChecked(false);
        ui->video_radioButton->setAutoExclusive(true);
    }
}

void YoutubeDl::clear_elements()
{
    setUrl("");
    setDir("");
    setUrl_title("");
    setUrl_format("");
}

bool YoutubeDl::download_audio()
{
    // Set the working directory to dir
    QDir::setCurrent(dir);
    qDebug() << "Changed current directory to : " << QDir::currentPath();
    QProcess dl_audio_proc;
    dl_audio_proc.start("youtube-dl --extract-audio --audio-format mp3 " + url);
    if(!dl_audio_proc.waitForFinished(-1) || dl_audio_proc.exitCode()!=0)
    {
        return false;
    }

    return true;
}

bool YoutubeDl::download_video()
{
    // Set the working directory to dir
    QDir::setCurrent(dir);
    //qDebug() << "Changed current directory to : " << QDir::currentPath();
    QProcess dl_audio_proc;
    dl_audio_proc.start("youtube-dl " + url);
    if(!dl_audio_proc.waitForFinished(-1) || dl_audio_proc.exitCode()!=0)
    {
        return false;
    }

    return true;
}

void YoutubeDl::on_download_button_clicked()
{
    if(url.isEmpty() || dir.isEmpty() || !( ui->audio_radioButton->isChecked() || ui->video_radioButton->isChecked() ) )
    {
        QMessageBox::critical(this, "ERROR", "Unsufficient data provided. Please try again by entering all needed fields!");
        on_information_action_triggered();
        return;
    }
    find_url_title();
    if(ui->audio_radioButton->isChecked())
    {
        if(download_audio())
        {
            ui->download_status_lineEdit->setText("Downloading song success");
            QMessageBox::information(this, "SUCCESS", "Successfully downloaded " + url_title + "!");
        } else
        {
            ui->download_status_lineEdit->setText("Downloading song failed");
            QMessageBox::critical(this, "FAILURE", "Download of " + url_title + " failed!");
        }
    }
    if(ui->video_radioButton->isChecked())
    {
        if(download_video())
        {
            ui->download_status_lineEdit->setText("Downloading video success");
            QMessageBox::information(this, "SUCCESS", "Successfully downloaded " + url_title + "!");
        } else
        {
            ui->download_status_lineEdit->setText("Downloading video failed");
            QMessageBox::critical(this, "FAILURE", "Download of " + url_title + " failed!");
        }
    }
    // Last clear all fields after download failure or success | Don't care about download outcome
    on_clear_fields_radioButton_clicked();
    // Also uncheck audio & video radio buttons
    uncheck_radio_buttons();
    // Last clear url, dir, url_title, url_format
    clear_elements();
}

/* ================================================================================================================================================= */
// Find the youtube-dl version
bool YoutubeDl::find_version()
{
    QProcess version_proc;
    version_proc.start("bash", QStringList() << "-c" << " youtube-dl --version ");\
    if(!version_proc.waitForFinished(3000) || version_proc.exitCode()!=0) {
        return false;
    }
    ytb_command_ver = version_proc.readAllStandardOutput();
    return true;
}


void YoutubeDl::on_actionyoutube_dl_command_version_triggered()
{
    if(find_version()==true)
    {
        QMessageBox::information(this, "Version", ytb_command_ver);
    }
    else {
        QMessageBox::critical(this, "ERROR", "youtube-dl is not installed in your system");
    }
}

/* ================================================================================================================================================= */
// Helper sub-function Check if youtube-dl is installed | Used by the install , update & remove youtube-dl command action trigger functions
bool YoutubeDl::is_ytb_command_Installed()
{
    QProcess ytb_proc;
    ytb_proc.start("which youtube-dl");
    ytb_proc.waitForFinished(3000);
    if(ytb_proc.exitStatus()==0)
    {
        return true;
    }
    return false;
}

// ANother two sub-functions for the installation of youtube-dl command
bool YoutubeDl::download_ytb_command()
{
    bool pass_entered;
    user_password = QInputDialog::getText(nullptr, "Downloading youtube-dl", "Please enter your password: ",
                                             QLineEdit::Password, "", &pass_entered);
    if(pass_entered==false || user_password.isEmpty())
    {
        return false;
    }

    QProcess passwd_proc, install_ytb_proc;
    passwd_proc.setStandardOutputProcess(&install_ytb_proc);
    passwd_proc.start("echo " + user_password);
    install_ytb_proc.start("sudo -S curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl");
    if(!passwd_proc.waitForFinished() || !install_ytb_proc.waitForFinished())
    {
        return false;
    }

    if(install_ytb_proc.exitCode()!=0)
    {
        QMessageBox::critical(this, "ERROR", "youtube-dl returned exit code 1");
    }

    return true;
}

bool YoutubeDl::make_exe()
{
    QProcess passwd_proc, exec_proc;
    passwd_proc.setStandardOutputProcess(&exec_proc);
    passwd_proc.start("echo " + user_password);
    exec_proc.start("sudo -S chmod a+rx /usr/local/bin/youtube-dl");
    if(!passwd_proc.waitForFinished() || !exec_proc.waitForFinished())
    {
        return false;
    }

    if(exec_proc.exitCode()!=0) {
        return false;
    }

    return true;
}

// Install youtube-dl | If not installed
void YoutubeDl::on_actionInstall_youtube_dl_command_triggered()
{
    if(is_ytb_command_Installed()==true)
    {
        QMessageBox::information(this, "INFORMATION", "No need. Youtube-dl is already installed in your system!");
        return;
    }

    if(download_ytb_command()==true && make_exe()==true)
    {
        QMessageBox::information(this, "SUCCESS", "youtube-dl successfully installed!");
        return;
    }
    else {
        QMessageBox::warning(this, "FAILURE", "youtube-dl failed to be installed!");
        return;
    }
}
/* ================================================================================================================================================= */
// Uninstall youtube-dl command | If installed only
bool YoutubeDl::remove_ytb_command()
{
    bool pass_entered;
    user_password = QInputDialog::getText(nullptr, "Removing youtube-dl", "Please enter your password: ",
                                             QLineEdit::Password, "", &pass_entered);
    if(pass_entered==false || user_password.isEmpty())
    {
        QMessageBox::critical(this, "ERROR", "Please enter your password and try again! No empty password accepted!");
        return false;
    }

    QProcess passwd_proc, remove_proc;
    passwd_proc.setStandardOutputProcess(&remove_proc);
    passwd_proc.start("echo " + user_password);
    remove_proc.start("sudo -S apt-get remove youtube-dl");
    if(!passwd_proc.waitForFinished() || !remove_proc.waitForFinished())
    {
        QMessageBox::critical(this, "ERROR", "The youtube-dl failed to be removed!");
        return false;
    }
    if(remove_proc.exitCode()!=0)
    {
        QMessageBox::critical(this, "ERROR", "Youtube-dl remove process returned exit code 1!");
        return false;
    }

    return true;
}


void YoutubeDl::on_actionRemove_youtube_dl_command_triggered()
{
    if(is_ytb_command_Installed()==false)
    {
        QMessageBox::information(this, "INFORMATION", "youtube-dl command is not installed. No need to remove!");
        return;
    }

    if(remove_ytb_command()==true)
    {
        QMessageBox::information(this, "INFORMATION", "youtube-dl command successfully removed from system!");
        return;
    }
    else {
        QMessageBox::warning(this, "WARNING", "youtube-dl command failed to be removed from system!");
        return;
    }
}
/* ================================================================================================================================================= */
// Update youtube-dl command | If installed only
bool YoutubeDl::update_ytb_command()
{
    bool pass_entered;
    user_password = QInputDialog::getText(nullptr, "Updating youtube-dl", "Please enter your password: ",
                                             QLineEdit::Password, "", &pass_entered);
    if(pass_entered==false || user_password.isEmpty())
    {
        QMessageBox::critical(this, "ERROR", "Please enter your password and try again! No empty password accepted!");
        return false;
    }

    QProcess passwd_proc, update_proc;
    passwd_proc.setStandardOutputProcess(&update_proc);
    passwd_proc.start("echo " + user_password);
    update_proc.start("sudo -S youtube-dl --update");
    if(!passwd_proc.waitForFinished() || !update_proc.waitForFinished())
    {
        QMessageBox::critical(this, "ERROR", "The youtube-dl failed to be updated!");
        return false;
    }
    if(update_proc.exitCode()!=0)
    {
        QMessageBox::critical(this, "ERROR", "Youtube-dl update process returned exit code 1!");
        return false;
    }

    return true;
}



void YoutubeDl::on_actionUpdate_youtube_dl_command_triggered()
{
    if(is_ytb_command_Installed()==false)
    {
        QMessageBox::information(this, "INFORMATION", "Cannot update youtube-dl since not installed!");
        return;
    }

    if(update_ytb_command()==true)
    {
        QMessageBox::information(this, "INFORMATION", "youtube-dl command successfully updated!");
        return;
    }
    else {
        QMessageBox::warning(this, "WARNING", "youtube-dl command failed to be updated!");
        return;
    }

}

/* ================================================================================================================================================= */
/*     Update I : Add functionality for conversion of an audio file or a video file to another format using the ffmpeg Linux command tool utility    */
/* ================================================================================================================================================= */
// I : Find the ffmpeg & it's used libraries versions and print them out in a MessageBox
bool YoutubeDl::is_ffmpeg_installed()
{
    QProcess f_proc;
    f_proc.start("which ffmpeg");
    f_proc.waitForFinished(5000);
    if(f_proc.exitStatus()==0)
    {
        return true;
    }
    return false;
}

bool YoutubeDl::find_ffmpeg_version()
{
    QProcess f_proc;
    f_proc.start("ffmpeg -version");
    f_proc.waitForFinished(5000);
    if(f_proc.exitStatus()!=0)
    {
        ffmpeg_version = "[]";
        return false;
    }
    ffmpeg_version = f_proc.readAllStandardOutput();
    return true;
}

void YoutubeDl::on_actionffmpeg_version_triggered()
{
    if(is_ffmpeg_installed()==true)
    {
        if(find_ffmpeg_version()==true)
        {
            QMessageBox::information(this, "VERSION", ffmpeg_version);
            return;
        }
        else {
            QMessageBox::warning(this, "WARRNING", "ffmpeg not installed!");
            return;
        }
    }
    else {
        QMessageBox::information(this, "INFORMATION", "ffmpeg command is NOT installed in your system!");
        return;
    }
}

/* ================================================================================================================================================= */
// Install ffmpeg | If not installed only
bool YoutubeDl::install_ffmpeg()
{
    bool pass_entered;
    user_password = QInputDialog::getText(nullptr, "Installing ffmpeg", "Please enter your password: ",
                                             QLineEdit::Password, "", &pass_entered);
    if(pass_entered==false || user_password.isEmpty())
    {
        QMessageBox::warning(this, "WARNING", "Please enter password and try again!");
        return false;
    }

    QProcess passwd_proc, install_proc;
    passwd_proc.setStandardOutputProcess(&install_proc);
    passwd_proc.start("echo " + user_password);
    install_proc.start("sudo -S apt-get install ffmpeg");
    if(!passwd_proc.waitForFinished() || !install_proc.waitForFinished())
    {
        return false;
    }
    if(install_proc.exitCode()!=0)
    {
        return false;
    }

    return true;
}


void YoutubeDl::on_actionInstall_ffmpeg_command_triggered()
{
    if(is_ffmpeg_installed()==true)
    {
        QMessageBox::information(this, "INFORMATION", "ffmpeg already installed in system!");
        return;
    }

    if(install_ffmpeg()==true)
    {
        QMessageBox::information(this, "INFORMATION", "ffmpeg command installed successfully!");
        return;
    }
    else {
        QMessageBox::critical(this, "ERROR", "ffmpeg command failed to be installed!");
        return;
    }
}

/* ================================================================================================================================================= */
// Remove ffmpeg command from the system
bool YoutubeDl::remove_ffmpeg()
{
    bool pass_entered;
    user_password = QInputDialog::getText(nullptr, "Removing ffmpeg", "Please enter your password: ",
                                             QLineEdit::Password, "", &pass_entered);
    if(pass_entered==false || user_password.isEmpty())
    {
        QMessageBox::warning(this, "WARNING", "Please enter password and try again!");
        return false;
    }

    QProcess passwd_proc, uninstall_proc;
    passwd_proc.setStandardOutputProcess(&uninstall_proc);
    passwd_proc.start("echo " + user_password);
    uninstall_proc.start("sudo -S apt-get remove ffmpeg");
    if(!passwd_proc.waitForFinished() || !uninstall_proc.waitForFinished())
    {
        return false;
    }
    if(uninstall_proc.exitCode()!=0)
    {
        return false;
    }

    return true;
}


void YoutubeDl::on_actionRemove_ffmpeg_command_triggered()
{
    if(is_ffmpeg_installed()==false)
    {
        QMessageBox::information(this, "INFORMATION", "ffmpeg is not installed in the system! No need to continue!");
        return;
    }

    if(remove_ffmpeg()==true)
    {
        QMessageBox::information(this, "INFORMATION", "ffmpeg successfully uninstalled!");
        return;
    }
    else {
        QMessageBox::critical(this, "ERROR", "ffmpeg failed to be uninstalled!");
        return;
    }
}
// END of ffmpeg toolbar related actions

/* ================================================================================================================================================= */
/*                                                      Conversion ffmpeg related actions                                                            */
/* ================================================================================================================================================= */
// take a path like /home/user/Music/filename.mp3 and keep only keep the filename and set it to the 'new_filename' QString variable
// Also append the .format in the end
void YoutubeDl::cut_filename()
{
    // COnvert filename to QFileInfo to use its power
    QFileInfo info(filename);
    // Keep only the base name from the absolute path name | Easy right ?
    filename = info.baseName();
}

// Fetch the filename absolute path from the selected file that the user selected
void YoutubeDl::on_old_filename_radioButton_clicked()
{
    QString home_dir = "/home/" + qgetenv("USER");
    filename = QFileDialog::getOpenFileName(this, tr("Select file"),
                                                             home_dir,
                                                             tr("All Files (*.*)") );
    ui->chosen_file_lineEdit->setText(filename);
    cut_filename();
    // Uncheck radio button
    ui->old_filename_radioButton->setAutoExclusive(false);
    ui->old_filename_radioButton->setChecked(false);
    ui->old_filename_radioButton->setAutoExclusive(true);
}

// Clear the ffmpeg section lineEdit buttons
void YoutubeDl::on_clear_ffmpeg_fields_pushButton_clicked()
{
    // Clear line Edits
    ui->chosen_file_lineEdit->setText("");
    ui->bitrate_lineEdit->setText("");
    ui->sampling_rate_lineEdit->setText("");
    ui->channels_lineEdit->setText("");
    ui->format_lineEdit->setText("");
    // Reset respective variables
    setFilename("");
    setNew_filename("");
    setFormat("");
}

// CONVERT PushButton main action
void YoutubeDl::create_new_filename()
{
    new_filename = filename + "." + format;
}

void YoutubeDl::setFormatBackup()
{
    QFileInfo info(ui->chosen_file_lineEdit->text());
    format_backup = info.completeSuffix();
}

bool YoutubeDl::convert()
{
    QFileInfo info(ui->chosen_file_lineEdit->text());
    QString saved_dir = info.path();
    QDir::setCurrent(saved_dir);
    //qDebug() << "Converting file in : " << saved_dir;

    QProcess ff_proc;
    // Example : ffmpeg -i filename.mp4 -vn -ar [sample_rate] -ac [channels] -ab [bit_rate] -f [format] new_filename
    QString ffmpeg_cmd = "ffmpeg -i \"" + filename + "." + format_backup + "\" -vn";
    if(!sample_rate.isEmpty())
    {
        ffmpeg_cmd += " -ar " + sample_rate;
    }
    if(!channels.isEmpty())
    {
        ffmpeg_cmd += " -ac " + channels;
    }
    if(!bit_rate.isEmpty())
    {
        ffmpeg_cmd += " -ab " + bit_rate;
    }
    if(!format.isEmpty())
    {
        ffmpeg_cmd += " -f " + format;
    }
    ffmpeg_cmd += " \"" + new_filename + "\"";
    //qDebug() << "ffmpeg cmd :: " << ffmpeg_cmd;
    //qDebug() << "ffmpge stdout : " << ff_proc.readAllStandardOutput();
    //qDebug() << "ffmpeg stderr : " << ff_proc.readAllStandardError();

    ff_proc.start(ffmpeg_cmd);
    if(!ff_proc.waitForFinished(20000))
    {
        return false;
    }
    if(ff_proc.exitCode()!=0)
    {
        return false;
    }
    return true;
}

void YoutubeDl::on_convert_pushButton_clicked()
{
    // Set appropriate variables
    setFormat(ui->format_lineEdit->text());
    setFormatBackup();
    //qDebug() << "FORMAT BACKUP = " << format_backup;
    create_new_filename();
    setFormat(ui->format_lineEdit->text());
    setChannels(ui->channels_lineEdit->text());
    setBit_rate(ui->bitrate_lineEdit->text());
    setSample_rate(ui->sampling_rate_lineEdit->text());
    //qDebug() << "Filename: " << filename << " NEW filename : " << new_filename;

    //
    if(filename.isEmpty() || format.isEmpty())
    {
        QMessageBox::information(this, "INFORMATION", "Filename and format of the converted file are compulsory. Enter both and try again!");
        return;
    }

    if(convert()==true)
    {
        QMessageBox::information(this, "INFORMATION", "File " + ui->chosen_file_lineEdit->text() + " converted to " + new_filename + " with success!");
        return;
    }
    else {
        QMessageBox::critical(this, "ERROR", "File " + ui->chosen_file_lineEdit->text() + " convertion to " + new_filename + " Failed!");
        return;
    }

}

// Add a toolbar action for opening a file | needed for the opening of files in the Conversion Section

void YoutubeDl::on_open_file_action_triggered()
{
    QString home_dir = "/home/" + qgetenv("USER");
    filename = QFileDialog::getOpenFileName(this, tr("Select file"),
                                            home_dir,
                                            tr("All Files (*.*)") );
    ui->chosen_file_lineEdit->setText(filename);
    cut_filename();
}
