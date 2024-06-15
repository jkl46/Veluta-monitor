function Decoder(bytes, port) {
    // Convert bytes to a string
    var decodedString = String.fromCharCode.apply(null, bytes);
  
    // Initialize variables to store chunks
    var chunks = [];
    var buffer = "";
    var receiving = false;
  
    // Iterate over each character in the decoded string
    for (var i = 0; i < decodedString.length; i++) {
      var char = decodedString.charAt(i);
      if (char === '#') {
        // Start receiving a new chunk
        receiving = true;
        buffer = "";
      } else if (char === '@') {
        // End of a chunk
        if (receiving) {
          chunks.push(buffer);
          buffer = "";
          receiving = false;
        }
      } else if (receiving) {
        // Collect characters for the current chunk
        buffer += char;
      }
    }
  
    // Define the keys for each chunk
    var keys = [
      'GPS_slave1_lat',
      'GPS_slave1_long',
      'GPS_slave2_lat',
      'GPS_slave2_long',
      'GPS_Hive_lat',
      'GPS_Hive_long',
      'DIST_master',
      'DIST_slave1',
      'DIST_slave2'
    ];
  
    // Create the output object
    var output = {};
  
    // Map chunks to their respective keys
    for (var j = 0; j < chunks.length; j++) {
      if (j < keys.length) {
        output[keys[j]] = chunks[j];
      } else {
        // If there are more chunks than keys, store them in an extra array
        if (!output.extra) {
          output.extra = [];
        }
        output.extra.push(chunks[j]);
      }
    }
  
    // Return the output object
    return output;
  }