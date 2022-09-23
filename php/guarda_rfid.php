<?php

    $conn = new mysqli("127.0.0.1", "pma", "", "clase");

    if ($conn->connect_error) {
        echo "Error in connection:" . $conn->connect_error . PHP_EOL;
        die();
    }

    
    $rfid = $_POST["rfid"];

    $query = "SELECT rfid FROM tarjeta";
    $result = $conn->query($query);
    $rfids = array();
    
    if ($result->num_rows > 0) {
        // output data of each row
        while($row = $result->fetch_assoc()) {
          array_push($rfids, $row["rfid"]);
          //echo $row["rfid"] . PHP_EOL;
        }
    } else {
        echo "0 results" . PHP_EOL;
    }

    /*
    foreach($rfids as $id){
        echo $id . "<br>";
    }*/

    //echo $rfid . PHP_EOL;
    if (in_array($rfid,$rfids)){
        echo "Existe en la bd" . PHP_EOL;
    }


    //$query = "INSERT INTO datos(dato,dato2,dato3) VALUES ($data, $data1, $data2)";

    //echo $query . PHP_EOL;


    $conn->close();
?>
