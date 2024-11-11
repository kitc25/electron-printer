const assert = require('assert/strict');
const { test, beforeEach } = require('node:test');

let addon;

beforeEach(() => {
  addon = require('../lib');
});
  
test('Ensure Non-functional apis do not lead any issues', (t) => {
    assert.ok(addon, 'Non-functional apis');
    // Add checks for specific functions if needed
    assert.strictEqual(typeof addon.getPrinter, 'function', 'Addon should have getPrinter');
  });

// Additional test cases 
test('Test getPrinter behavior', (t) => {
  const result = addon.getPrinter();
  assert.strictEqual(result, 'getPrinter is not implemented yet, request for a PR if required', 'getPrinter is not implemented yet, request for a PR if required"');
});
