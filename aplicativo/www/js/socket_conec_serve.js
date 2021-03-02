  var socket = io.connect("http://192.168.0.101:8080");
       socket.on("g@g", function (data) {
           event_soket.tratamento(data);

          });