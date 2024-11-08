const assert = require('assert/strict');
const { test, beforeEach } = require('node:test');

let addon;

beforeEach(() => {
  addon = require('../lib');
});

test('Ensure printDirect function exists', (t) => {
  assert.ok(addon.printDirect, 'printDirect function should exist');
  assert.strictEqual(typeof addon.printDirect, 'function', 'printDirect should be a function');
});

test('Ensure printDirect throws error when no arguments are passed', (t) => {
  assert.throws(() => {
    addon.printDirect();
  }, /Error/, 'printDirect should throw an error when no arguments are passed');
});

test('Ensure printDirect works properly', (t) => {
  addon.printDirect(1,2,3,4,5);
});