wget -O xc8-v2.45-linux.run https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v2.45-full-install-linux-x64-installer.run
chmod +x xc8-v2.45-linux.run
sudo ./xc8-v2.45-linux.run --mode unattended --unattendedmodeui none --netservername localhost > file
echo "/opt/microchip/xc8/v2.45/bin/" >> $GITHUB_PATH
#export PATH="/opt/microchip/xc8/v2.45/bin/:$PATH"
