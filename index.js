const testAddon = require('./build/Release/testaddon.node');


/*
console.log('===================');
console.log('You can use these function');
console.log(testAddon);
console.log('===================');
*/


//you can get your pointgreycamera serial number

/*
var myresults1 = testAddon.ConnectCamera();
console.log("get serialnumber:" + myresults1);


var imagearray;

setTimeout(function () {
   imagearray = testAddon.CaptureCamera();


   var buffer1 = new Buffer.alloc(imagearray.length);
   var uint8 = new Uint8Array(imagearray);
   buffer1.set(uint8);
   buffer1 = buffer1.toString('base64');
   //console.log(buffer1); 



   require("fs").writeFile("out.jpg", buffer1, 'base64', function (err) {
      console.log(err);
   });
   //console.log("버퍼길이:"+buffer1.length);
   var myresults3 = testAddon.DisConnectCamera();
   console.log("camera disconnect:" + myresults3);
}, 100);
*/
 




//hello test
/*
console.log(testAddon.hello());
*/


//cursor setting test
/*
console.log(testAddon.GetCursor());
console.log(testAddon.SetCursor(0,0));
*/




//detect key press [esc] key  or  mouse left click
/*
function detect()
{
   return new Promise(function(resolve){
      var a = testAddon.IsterminateCalibration();
      resolve(a);
   });
}

detect().then(function(results){
   console.log("your calibration is terminated by use click mouse or keypress esc");
});
*/



//console.log(testAddon.IsterminateCalibration()); mouseclick or press [esc] key detect;





// make event  (keyboard press and mouseclick) 
/*
console.log(testAddon.ClickMouseLeft());
console.log(testAddon.PressKeyboard(65)); //122  
//https://docs.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
*/







module.exports = testAddon;
