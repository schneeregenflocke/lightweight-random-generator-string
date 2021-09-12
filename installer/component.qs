function Component() {}

Component.prototype.createOperations = function() {
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation(
            "CreateShortcut",
            "@TargetDir@/SimpleRandomStringGenerator/SimpleRandomStringGenerator.exe", 
            "@StartMenuDir@/SimpleRandomStringGenerator.lnk"
        );        
    }
}