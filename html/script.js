const APPID = "ConnectionTest";
    const KEY = "VAIZiRoq8FTak5K";
    const SECRET = "ubB65nfQRoyXWr0umxPPPJ9ZX";

    const ALIAS = "htmlKey2";         //  ชื่อตัวเอง
    const thing1 = "esp";          //  ชื่อเพื่อนที่จะคุย

  function switchPress(logic){
    if(logic == 1 ){
      microgear.chat(thing1,"ON");
      console.log("ON");
    }else if(logic == 0 ){
      microgear.chat(thing1,"OFF");
      console.log("OFF");
    }
  }

    var microgear = Microgear.create({
        key: KEY,
        secret: SECRET,
        alias : ALIAS
    });


     microgear.on('message', function(topic,data) {
        if(parseFloat(data)<1){
         document.getElementById("Status").innerHTML =  "Room is empty.";
         microgear.chat(thing1,"OFF");
        }else if(parseFloat(data)>=1){
          document.getElementById("Status").innerHTML =  "Detected!"; 
          microgear.chat(thing1,"ON");
        }
        console.log(data);
    });

    microgear.on('connected', function() {
     microgear.setAlias(ALIAS);
      document.getElementById("connected_NETPIE").innerHTML = "server connection status : Connected to NETPIE"
    });

     microgear.on('present', function(event) {
     console.log(event);
    });

     microgear.on('absent', function(event) {
     console.log(event);
     });

     microgear.resettoken(function(err) {
     microgear.connect(APPID);
    });
