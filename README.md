#Flycapture2  sdk is wrapped on Node JS by ADDON

***
- 2019-10-01  Success to get Image by node.js <bmp format> 
- 2019-10-22  Copy dll file to XXX.node 's location  
***


# How to Use?

```
const flycapture2 = require('sample-flycapture2-addon');



//If you success to connect,you can get your pointgreycamera serial number  (
var myresults1 = flycapture2.ConnectCamera();
console.log("get serialnumber:" + myresults1);

if(myresults1)
{
   setTimeout(function () {
      var imagearray;
      imagearray = flycapture2.CaptureCamera(); //jpg image captured array
      var buffer1 = new Buffer.alloc(imagearray.length);
      var uint8 = new Uint8Array(imagearray);
      buffer1.set(uint8);
      buffer1 = buffer1.toString('base64');
      //console.log(buffer1);  //buffer1 is base64 rawdata (jpg)

      require("fs").writeFile("out.jpg",buffer1, 'base64', function (err) {
         console.log(err);
      });

      var myresults3 = flycapture2.DisConnectCamera();
      console.log("camera disconnect:" + myresults3);

   }, 100); //For capturing image , need more time until connectcamera 
}

```