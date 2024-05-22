# winevt-EvtSubscribe-EventRecordID-issue

Repository for reproducing issue of some event being skipped when using [EvtSubscribe](https://learn.microsoft.com/en-us/windows/win32/api/winevt/nf-winevt-evtsubscribe) with [EventRecordID](https://learn.microsoft.com/en-us/windows/win32/wes/eventschema-eventrecordid-systempropertiestype-element). Source code referenced from [Subscribing to Events](https://learn.microsoft.com/en-us/windows/win32/wes/subscribing-to-events).

## Requirement

Visual Studio 2017 or later required to compile program.

## How to build

- Open winevt_subscribe.sln with Visual Studio.
- Run Build Solution from the Build menu or press Ctrl+Shift+B.
- The compiled program is to be located at .\\(x64\\)Debug\\winevt_subscribe.exe.

## Details

The compiled program can be used like

```cmd
winevt_subscribe.exe "[event channel]" "[query string]"
```

When running the program like this

```cmd
winevt_subscribe.exe "Application" "Event/System[EventRecordID>8000]"
```

some events skipped while printing the events(discontinuous EventRecordID). 

_※ Event log cleared beforehand for testing._


_Using push subscription method_

![push method](https://imgur.com/a/IRbqAAI)

<details>
<summary>Getting events using Get-EventLog from powershell</summary>

```powershell
PS C:\Users\user> Get-EventLog -LogName Application | Select-Object Index, EntryType, Source, Message

Index EntryType Source      Message
----- --------- ------      -------
 8846     Error EventCreate test event log
 8845     Error EventCreate test event log
 8844     Error EventCreate test event log
 8843     Error EventCreate test event log
 8842     Error EventCreate test event log
 8841     Error EventCreate test event log
 8840     Error EventCreate test event log
 8839     Error EventCreate test event log
 8838     Error EventCreate test event log
 8837     Error EventCreate test event log
 8836     Error EventCreate test event log
 8835     Error EventCreate test event log
 8834     Error EventCreate test event log
 8833     Error EventCreate test event log
 8832     Error EventCreate test event log
 8831     Error EventCreate test event log
 8830     Error EventCreate test event log
 8829     Error EventCreate test event log
 8828     Error EventCreate test event log
 8827     Error EventCreate test event log
 8826     Error EventCreate test event log
 8825     Error EventCreate test event log
 8824     Error EventCreate test event log
 8823     Error EventCreate test event log
 8822     Error EventCreate test event log
 8821     Error EventCreate test event log
 8820     Error EventCreate test event log
 8819     Error EventCreate test event log
 8818     Error EventCreate test event log
 8817     Error EventCreate test event log
 8816     Error EventCreate test event log
 8815     Error EventCreate test event log
 8814     Error EventCreate test event log
 8813     Error EventCreate test event log
 8812     Error EventCreate test event log
 8811     Error EventCreate test event log
 8810     Error EventCreate test event log
 8809     Error EventCreate test event log
 8808     Error EventCreate test event log
 8807     Error EventCreate test event log
 8806     Error EventCreate test event log
 8805     Error EventCreate test event log
 8804     Error EventCreate test event log
 8803     Error EventCreate test event log
 8802     Error EventCreate test event log
 8801     Error EventCreate test event log
 8800     Error EventCreate test event log
 8799     Error EventCreate test event log
 8798     Error EventCreate test event log
 8797     Error EventCreate test event log
 8796     Error EventCreate test event log
 8795     Error EventCreate test event log
 8794     Error EventCreate test event log
 8793     Error EventCreate test event log
 8792     Error EventCreate test event log
 8791     Error EventCreate test event log
 8790     Error EventCreate test event log
 8789     Error EventCreate test event log
 8788     Error EventCreate test event log
 8787     Error EventCreate test event log
 8786     Error EventCreate test event log
 8785     Error EventCreate test event log
 8784     Error EventCreate test event log
 8783     Error EventCreate test event log
 8782     Error EventCreate test event log
 8781     Error EventCreate test event log
 8780     Error EventCreate test event log
 8779     Error EventCreate test event log
 8778     Error EventCreate test event log
 8777     Error EventCreate test event log
 8776     Error EventCreate test event log
 8775     Error EventCreate test event log
 8774     Error EventCreate test event log
 8773     Error EventCreate test event log
 8772     Error EventCreate test event log
 8771     Error EventCreate test event log
 8770     Error EventCreate test event log
 8769     Error EventCreate test event log
 8768     Error EventCreate test event log
 8767     Error EventCreate test event log
 8766     Error EventCreate test event log
 8765     Error EventCreate test event log
 8764     Error EventCreate test event log
 8763     Error EventCreate test event log
 8762     Error EventCreate test event log
 8761     Error EventCreate test event log
 8760     Error EventCreate test event log
 8759     Error EventCreate test event log
 8758     Error EventCreate test event log
 8757     Error EventCreate test event log
 8756     Error EventCreate test event log
 8755     Error EventCreate test event log
 8754     Error EventCreate test event log
 8753     Error EventCreate test event log
 8752     Error EventCreate test event log
```
</details>

_Using subscription pull method_

![pull method](https://imgur.com/a/jHcKVdY)

<details>
<summary>Getting events using Get-EventLog from powershell</summary>

```powershell
PS C:\Users\user> Get-EventLog -LogName Application | Select-Object Index, EntryType, Source, Message

Index EntryType Source      Message
----- --------- ------      -------
 9060     Error EventCreate test event log
 9059     Error EventCreate test event log
 9058     Error EventCreate test event log
 9057     Error EventCreate test event log
 9056     Error EventCreate test event log
 9055     Error EventCreate test event log
 9054     Error EventCreate test event log
 9053     Error EventCreate test event log
 9052     Error EventCreate test event log
 9051     Error EventCreate test event log
 9050     Error EventCreate test event log
 9049     Error EventCreate test event log
 9048     Error EventCreate test event log
 9047     Error EventCreate test event log
 9046     Error EventCreate test event log
 9045     Error EventCreate test event log
 9044     Error EventCreate test event log
 9043     Error EventCreate test event log
 9042     Error EventCreate test event log
 9041     Error EventCreate test event log
 9040     Error EventCreate test event log
 9039     Error EventCreate test event log
 9038     Error EventCreate test event log
 9037     Error EventCreate test event log
 9036     Error EventCreate test event log
 9035     Error EventCreate test event log
 9034     Error EventCreate test event log
 9033     Error EventCreate test event log
 9032     Error EventCreate test event log
 9031     Error EventCreate test event log
 9030     Error EventCreate test event log
 9029     Error EventCreate test event log
 9028     Error EventCreate test event log
 9027     Error EventCreate test event log
 9026     Error EventCreate test event log
 9025     Error EventCreate test event log
 9024     Error EventCreate test event log
 9023     Error EventCreate test event log
 9022     Error EventCreate test event log
 9021     Error EventCreate test event log
 9020     Error EventCreate test event log
 9019     Error EventCreate test event log
 9018     Error EventCreate test event log
 9017     Error EventCreate test event log
 9016     Error EventCreate test event log
 9015     Error EventCreate test event log
 9014     Error EventCreate test event log
 9013     Error EventCreate test event log
 9012     Error EventCreate test event log
 9011     Error EventCreate test event log
 9010     Error EventCreate test event log
 9009     Error EventCreate test event log
 9008     Error EventCreate test event log
 9007     Error EventCreate test event log
 9006     Error EventCreate test event log
 9005     Error EventCreate test event log
 9004     Error EventCreate test event log
 9003     Error EventCreate test event log
 9002     Error EventCreate test event log
 9001     Error EventCreate test event log
 9000     Error EventCreate test event log
 8999     Error EventCreate test event log
 8998     Error EventCreate test event log
 8997     Error EventCreate test event log
 8996     Error EventCreate test event log
 8995     Error EventCreate test event log
 8994     Error EventCreate test event log
 8993     Error EventCreate test event log
 8992     Error EventCreate test event log
 8991     Error EventCreate test event log
 8990     Error EventCreate test event log
 8989     Error EventCreate test event log
 8988     Error EventCreate test event log
 8987     Error EventCreate test event log
 8986     Error EventCreate test event log
 8985     Error EventCreate test event log
 8984     Error EventCreate test event log
 8983     Error EventCreate test event log
 8982     Error EventCreate test event log
 8981     Error EventCreate test event log
 8980     Error EventCreate test event log
 8979     Error EventCreate test event log
 8978     Error EventCreate test event log
 8977     Error EventCreate test event log
 8976     Error EventCreate test event log
 8975     Error EventCreate test event log
 8974     Error EventCreate test event log
 8973     Error EventCreate test event log
 8972     Error EventCreate test event log
 8971     Error EventCreate test event log
 8970     Error EventCreate test event log
 8969     Error EventCreate test event log
 8968     Error EventCreate test event log
 8967     Error EventCreate test event log
 8966     Error EventCreate test event log
 8965     Error EventCreate test event log
 8964     Error EventCreate test event log
 8963     Error EventCreate test event log
 8962     Error EventCreate test event log
 8961     Error EventCreate test event log
 8960     Error EventCreate test event log
 8959     Error EventCreate test event log
 8958     Error EventCreate test event log
 8957     Error EventCreate test event log
 8956     Error EventCreate test event log
 8955     Error EventCreate test event log
 8954     Error EventCreate test event log
 8953     Error EventCreate test event log
 8952     Error EventCreate test event log
 8951     Error EventCreate test event log
 8950     Error EventCreate test event log
 8949     Error EventCreate test event log
 8948     Error EventCreate test event log
 8947     Error EventCreate test event log
 8946     Error EventCreate test event log
 8945     Error EventCreate test event log
 8944     Error EventCreate test event log
 8943     Error EventCreate test event log
 8942     Error EventCreate test event log
 8941     Error EventCreate test event log
 8940     Error EventCreate test event log
 8939     Error EventCreate test event log
 8938     Error EventCreate test event log
 8937     Error EventCreate test event log
 8936     Error EventCreate test event log
 8935     Error EventCreate test event log
 8934     Error EventCreate test event log
 8933     Error EventCreate test event log
 8932     Error EventCreate test event log
 8931     Error EventCreate test event log
 8930     Error EventCreate test event log
 8929     Error EventCreate test event log
 8928     Error EventCreate test event log
 8927     Error EventCreate test event log
 8926     Error EventCreate test event log
 8925     Error EventCreate test event log
 8924     Error EventCreate test event log
 8923     Error EventCreate test event log
 8922     Error EventCreate test event log
 8921     Error EventCreate test event log
 8920     Error EventCreate test event log
 8919     Error EventCreate test event log
 8918     Error EventCreate test event log
 8917     Error EventCreate test event log
 8916     Error EventCreate test event log
 8915     Error EventCreate test event log
 8914     Error EventCreate test event log
 8913     Error EventCreate test event log
 8912     Error EventCreate test event log
 8911     Error EventCreate test event log
 8910     Error EventCreate test event log
 8909     Error EventCreate test event log
 8908     Error EventCreate test event log
 8907     Error EventCreate test event log
 8906     Error EventCreate test event log
 8905     Error EventCreate test event log
 8904     Error EventCreate test event log
 8903     Error EventCreate test event log
 8902     Error EventCreate test event log
 8901     Error EventCreate test event log
 8900     Error EventCreate test event log
 8899     Error EventCreate test event log
 8898     Error EventCreate test event log
 8897     Error EventCreate test event log
 8896     Error EventCreate test event log
 8895     Error EventCreate test event log
 8894     Error EventCreate test event log
 8893     Error EventCreate test event log
 8892     Error EventCreate test event log
 8891     Error EventCreate test event log
 8890     Error EventCreate test event log
 8889     Error EventCreate test event log
 8888     Error EventCreate test event log
 8887     Error EventCreate test event log
 8886     Error EventCreate test event log
 8885     Error EventCreate test event log
 8884     Error EventCreate test event log
 8883     Error EventCreate test event log
 8882     Error EventCreate test event log
 8881     Error EventCreate test event log
 8880     Error EventCreate test event log
 8879     Error EventCreate test event log
 8878     Error EventCreate test event log
 8877     Error EventCreate test event log
 8876     Error EventCreate test event log
 8875     Error EventCreate test event log
 8874     Error EventCreate test event log
 8873     Error EventCreate test event log
 8872     Error EventCreate test event log
 8871     Error EventCreate test event log
 8870     Error EventCreate test event log
 8869     Error EventCreate test event log
 8868     Error EventCreate test event log
 8867     Error EventCreate test event log
 8866     Error EventCreate test event log
 8865     Error EventCreate test event log
 8864     Error EventCreate test event log
 8863     Error EventCreate test event log
 8862     Error EventCreate test event log
 8861     Error EventCreate test event log
 8860     Error EventCreate test event log
 8859     Error EventCreate test event log
 8858     Error EventCreate test event log
 8857     Error EventCreate test event log
 8856     Error EventCreate test event log
 8855     Error EventCreate test event log
 8854     Error EventCreate test event log
 8853     Error EventCreate test event log
```
</details>
