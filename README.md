# Flycapture2 SDK wrapped  
You can get image at GP3 device.  
# Configuration  
OS : Windows 10  
node --version : 10.16.3  
[node-gyp configuration] must finish  before using this module.  
you can learn about node-gyp at here.  
https://www.npmjs.com/package/node-gyp  
# Warning  
GP3 device can not share capture images  
# How to Use?

```
const flycapture2 = require('flycapture2-sdk');
//If you success to connect,
//you can get your pointgreycamera serial number
var serialnumber = flycapture2.ConnectCamera();
console.log("get serialnumber:" + serialnumber);

if(myresults1){

  setTimeout(function () {
      var imagearray; 
      //image array are captured by jpg format 
      imagearray = flycapture2.CaptureCamera();

      var buffer1 = new Buffer.alloc(imagearray.length);
      var uint8 = new Uint8Array(imagearray);
      buffer1.set(uint8);
      buffer1 = buffer1.toString('base64');
      //console.log(buffer1);  
      //buffer1 is base64 rawdata (jpg)

      require("fs").writeFile("out.jpg",buffer1, 'base64', 
      function (err) {
         console.log(err);
      });

      var myresults3 = flycapture2.DisConnectCamera();
      console.log("camera disconnect:" + myresults3);

  }, 100);
  //For capturing image , need more time until connectcamera 
}

```