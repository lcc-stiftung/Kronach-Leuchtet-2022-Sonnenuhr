#include <Arduino.h>

const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
    
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Sonnenuhr</title>

        <style>

            html{
                background-color: #ff582e;
                background-color: #151e28;
                color: #ffffff;
                text-align: center;
                font-family: Arial, Helvetica, sans-serif;
            }

            #logo{
                width: 80%;
                margin-left: 10%;
            }

            #logo img{
                width: 200px;
                background-color: rgba(255, 255, 255, 0.01);
                border-radius: 50%;
            }

            h1{
                font-size: 30px;
                text-transform: uppercase;
                font-weight: 100;
            }

            h2{
                font-size: 25px;
                font-weight: 200;
                color: #ff582e;
            }

            .currentColor{
                padding: 0.5rem 1.2rem;
                background-color: rgba(255, 255, 255, 0.01);;
            }

            #chooseColor, #currentColor{
                margin-top: 3rem;
            }

            button{
                display: inline-block;
                width: 100px;
                border: none;
                padding: 0.5rem 2rem;
            }

            .red{
                background-color: red;
                color: #ffffff;
            }

            .green{
                background-color: green;
                color: #ffffff;
            }

            .blue{
                background-color: blue;
                color: #ffffff;
            }

            .yellow{
                background-color: yellow;
                color: #222222;
            }

            .orange{
                background-color: orange;
                color: #222222;
            }

            .purple{
                background-color: purple;
                color: #ffffff;
            }

            #row{
                margin-top: 1rem;
            }


        </style>
    </head>

    <body>

        <div id="logo">
            <img src="LCC 500x500.png" alt="">
            <h1>Lucas Cranach Campus Stiftung</h1>
            <h2>Sonnenuhr</h2>
            
        </div>

        <div id="currentColor">
            <p>Aktuelle Farbe:</p>
            <span class="currentColor" id="currentColor">Gr??n</span>
        </div>

        <div id="chooseColor">
            <p>Farbe W??hlen:</p>
            <button type="button" onclick="sendData(red)" class="red">Rot</button>
            <button type="button" onclick="sendData(green)" class="green">Gr??n</button>
            <button type="button" onclick="sendData(blue)" class="blue">Blau</button>
        </div>

        <div id="row">
            <button type="button" onclick="sendData(yellow)" class="yellow">Gelb</button>
            <button type="button" onclick="sendData(orange)" class="orange">Orange</button>
            <button type="button" onclick="sendData(purple)" class="purple">Lila</button>
        </div>

        <script>

            function sendData(color) {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("LEDState").innerHTML =
                        this.responseText;
                    }
                };
                xhttp.open("GET", "setColor?chosenColor="+color, true);
                xhttp.send();
            }

            setInterval(function() {
                // Call a function repetatively with 1 Second interval
                getData();
            }, 2000); //1000mSeconds update rate

            function getData() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("currentColor").innerHTML =
                    this.responseText;
                    }   
                };
                xhttp.open("GET", "readColor", true);
                xhttp.send();
            }

        </script>
        
    </body>
</html>

)=====";