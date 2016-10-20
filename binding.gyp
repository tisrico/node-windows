{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "win-node.cc", "myobject.cc", "sandbox.cc", "nodeWindow.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ]
    }
  ]
}
