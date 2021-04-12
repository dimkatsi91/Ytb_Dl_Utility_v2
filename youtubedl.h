/*
 * Author : dimos katsimardos
 * Date   : 2019, August 16
 * Update I : Add functionality for audio & video converting
 *            using the well known Linux command ffmpeg
 */
#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QTime>
#include <QFileInfo>

namespace Ui {
class YoutubeDl;
}

class YoutubeDl : public QMainWindow
{
    Q_OBJECT

public:
    explicit YoutubeDl(QWidget *parent = nullptr);
    ~YoutubeDl();
    // Setter & Getter for url string
    QString getUrl() const;
    void setUrl(const QString &value);
    // Setter & Getter for dir string
    QString getDir() const;
    void setDir(const QString &value);
    // bool function that checks if a selected directory is a valid one
    bool check_if_dir_is_valid(QString &dir_name);
    // Setter & Getter for url_title string
    QString getUrl_title() const;
    void setUrl_title(const QString &value);
    // Setter & Getter for url_format string
    QString getUrl_format() const;
    void setUrl_format(const QString &value);
    // Find the url's title
    bool find_url_title();
    // Find the url's format
    bool find_url_format();
    // QProcess for audio download
    bool download_audio();
    // QProcess for video download
    bool download_video();
    // Set pixamaps for audio & video icons
    void setPixmaps();
    //  Uncheck audio & video radio buttons
    void uncheck_radio_buttons();
    // Clear strings url, dir, url_title & url_format
    void clear_elements();
    // Find youtube-dl Linux command version
    bool find_version();
    // Check if youtube-dl is installed in the system
    bool is_ytb_command_Installed();
    // Get/Download youtube-dl command from GitHub official page
    bool download_ytb_command();
    // Make the youtube-dl command executable
    bool make_exe();
    // Remove/Uninstall youtube-dl command
    bool remove_ytb_command();
    // update youtube-dl command
    bool update_ytb_command();
    // ffmpeg related functions / actions
    bool is_ffmpeg_installed();
    // Set the ffmpeg_version string
    bool find_ffmpeg_version();
    // Install ffmpeg using a QProcess
    bool install_ffmpeg();
    // Remove / Uninstall ffmpeg command usign a QProcess
    bool remove_ffmpeg();
    // Cut and keep only the filename from the absolute path's whole path_filename
    void cut_filename();
    // Create the new_filename
    void create_new_filename();
    // Convert a filename to new_filename using ffmpeg QProcess
    bool convert();
    // Set the format from the filename which is cutted
    void setFormatBackup();

    QString getFilename() const;
    void setFilename(const QString &value);

    QString getFormat() const;
    void setFormat(const QString &value);

    QString getNew_filename() const;
    void setNew_filename(const QString &value);

    QString getSample_rate() const;
    void setSample_rate(const QString &value);

    QString getBit_rate() const;
    void setBit_rate(const QString &value);

    QString getChannels() const;
    void setChannels(const QString &value);

private slots:
    void on_confirm_button_clicked();

    void on_explore_directory_radioButton_clicked();

    void on_clear_fields_radioButton_clicked();

    void clear_fields();

    void on_print_url_title_radioButton_clicked(bool checked);

    void on_print_url_format_radioButton_clicked(bool checked);

    void on_exit_button_clicked();

    void on_information_button_clicked();

    void on_information_action_triggered();

    void on_exit_application_action_triggered();

    void on_about_app_action_triggered();

    void on_actionAbout_Youtube_dl_Utility_triggered();

    void on_about_author_action_triggered();

    void on_download_button_clicked();

    void on_open_folder_action_triggered();

    void on_actionyoutube_dl_command_version_triggered();

    void on_actionInstall_youtube_dl_command_triggered();

    void on_actionRemove_youtube_dl_command_triggered();

    void on_actionUpdate_youtube_dl_command_triggered();

    void on_actionffmpeg_version_triggered();

    void on_actionInstall_ffmpeg_command_triggered();

    void on_actionRemove_ffmpeg_command_triggered();

    void on_old_filename_radioButton_clicked();

    void on_clear_ffmpeg_fields_pushButton_clicked();

    void on_convert_pushButton_clicked();

    void on_open_file_action_triggered();

private:
    Ui::YoutubeDl *ui;
    // url and directory string variables
    QString url;
    QString dir;
    // url title and format
    QString url_title;
    QString url_format;
    // Linux command youtube-dl version string
    QString ytb_command_ver;
    // User's password to download/make executable youtube-dl program
    QString user_password;
    // ffmpeg QString variable
    QString ffmpeg_version;
    // filename to be converted using ffmpeg command
    QString filename;
    // new filename format
    QString format_backup;
    QString format;
    QString new_filename;
    // Audio Sampling rate | Audio Bit Rate | Audio Channels
    QString sample_rate;
    QString bit_rate;
    QString channels;
};

#endif // YOUTUBEDL_H
