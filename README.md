# Youtube-dl GUI Utility 

Title  : Youtube-dl GUI

Author : Dimos Katsimardos

Date   : August 16, 2019

Dev Environment  : Qt Creator 4.9.2 Open Source Community Edition

Work Environment : Ubuntu Linux 18.04 LTS

GUI Version      : v1.1.0

Update regarding ffmpeg conversion : Check the ffmpeg command various used libraries versions, install and remove ffmpeg toobar actions added. 

After having downloaded the source code package, make the appimage executable file able to be executed by giving the correct permissions and then run it!

-------------------------------------------------------------------------------------------------------------------------------

# Information

This GUI is supported under next prerequisites :

* Linux | Mostly Debian-based Distros
* ffmpeg or similar utility needs to be installed for the audio | video download option
* youtube-dl program needs to be installed
* Qt Creator 4.9.2 is recommended to be installed in order to open this GUI. You can also run directly the AppImage executable, since Qt is not prerequisite in this case

-------------------------------------------------------------------------------------------------------------------------------

## Example: 

- Main Window:

![Main Window](https://github.com/dimkatsi91/Ytb_Dl_Utility_v2/blob/main/samples/App_main_window.png)

#### Toolbar Provided Actions/Options:

- Start section gives next options:
- Open Explorer and Select a folder for the url to be saved
- Information on how to use this GUI Application
- Exit the application
    
#### Help section gives next options:
- General information about this application
- Information about the Author of this application
- The YoutubeDl GUI Utility / Application versioning information
    
#### youtube-dl Actions gives next options:
- Print the version of the youtube-dl Linux command
- Install youtube-dl Linux command
- Remove youtube-dl Linux command
- Update youtube-dl Linux command

#### ffmpeg Actions gives next options:
- ffmpeg libraries versioning print-out
- ffmpeg installation capability
- ffmpeg removal capability
    
#### Audio & Video Conversion Options:
 
- [Compulsory] Select a file from your system
- [Optional] Enter the sampling rate, for example 44100 Hz
- [Optional] Enter the bit rate, for example 192
- [Optional] Enter the audio channels number
- [Compulsory] Enter the output format of the file that is chosen and will be converted
- Push the 'CONVERT' button and the file conversion will be executed. A message will appear upon success or failure!
- Above fields can be cleared by pressing the button 'Clear ffmpeg fields'
