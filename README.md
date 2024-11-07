# @susheer/electron-printer

`@susheer/electron-printer` is a Node.js and Electron.js addon for printing barcodes on barcode printers. This project leverages Node-API (N-API) to ensure compatibility and stability across different Node.js versions and environments. Currently, it supports Windows only.

## Features

- **Print Barcodes**: Easily print barcodes on supported barcode printers.
- **Node-API (N-API)**: Utilizes N-API for better stability and compatibility across Node.js versions.
- **Electron.js Integration**: Seamlessly integrates with Electron.js for desktop applications.
- **Windows Support**: Currently supports Windows operating systems.

## Installation

To install `@susheer/electron-printer`, use npm:

```bash
npm install @susheer/electron-printer
```

## Usage

Here's a basic example of how to use `@susheer/electron-printer` in a Node.js or Electron.js application:

```javascript
const printer = require('@susheer/electron-printer');

// Example function to print a barcode
function printBarcode(data) {
    printer.print(data, (err) => {
        if (err) {
            console.error('Error printing barcode:', err);
        } else {
            console.log('Barcode printed successfully!');
        }
    });
}

// Sample barcode data
const barcodeData = {
    type: 'CODE128',
    data: '1234567890',
    options: {
        width: 2,
        height: 100,
        displayValue: true
    }
};

// Print the barcode
printBarcode(barcodeData);
```

## API

### `print(data, callback)`

Prints a barcode with the specified data.

- `data`: An object containing the barcode type, data, and options.
  - `type`: The type of barcode (e.g., `CODE128`, `EAN13`).
  - `data`: The data to encode in the barcode.
  - `options`: Additional options for barcode printing (e.g., width, height, displayValue).
- `callback`: A callback function that is called when the printing is complete or if an error occurs.

## Building from Source

To build `@susheer/electron-printer` from source, you need to have Node.js and npm installed. Then, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/Susheer/electron-printer.git
    cd @susheer/electron-printer
    ```

2. Install dependencies:
    ```bash
    npm install
    ```

3. Build the addon:
    ```bash
    npm run build
    ```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## License

This project is licensed under the MIT License.

---

Feel free to copy and paste this into your README file on GitHub! If you need any more adjustments or additions, just let me know.
