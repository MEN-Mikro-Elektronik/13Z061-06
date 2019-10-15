<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="page">
    <filename>index</filename>
    <title></title>
    <name>index</name>
    <docanchor>codes</docanchor>
    <docanchor>Variants</docanchor>
    <docanchor>Documents</docanchor>
    <docanchor>z61_pwm_min</docanchor>
    <docanchor>interrupts</docanchor>
    <docanchor>General</docanchor>
    <docanchor>api_functions</docanchor>
    <docanchor>FuncDesc</docanchor>
    <docanchor>z61_pwm_max</docanchor>
    <docanchor>reading</docanchor>
    <docanchor>descriptor_entries</docanchor>
    <docanchor>z61_simp</docanchor>
  </compound>
  <compound kind="file">
    <name>z61_ctrl.c</name>
    <path>/opt/menlinux/DRIVERS/MDIS_LL/Z061_PWM/TOOLS/Z61_CTRL/COM/</path>
    <filename>z61__ctrl_8c</filename>
    <member kind="define">
      <type>#define</type>
      <name>ERR_OK</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERR_PARAM</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERR_FUNC</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEF_CLK</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>Usage</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>PrintError</name>
      <anchor>a11</anchor>
      <arglist>(char *info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Time2Clock</name>
      <anchor>a12</anchor>
      <arglist>(int32 sysFreq, int32 timeUs)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>ConfigPwm</name>
      <anchor>a13</anchor>
      <arglist>(int32 sysFreq, int32 cycleClk, int32 pulseClk)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>PrintPwmSetting</name>
      <anchor>a14</anchor>
      <arglist>(int32 sysFreq, int32 cycleClk, int32 pulseClk)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a15</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char</type>
      <name>IdentString</name>
      <anchor>a4</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>MDIS_PATH</type>
      <name>G_path</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>u_int32</type>
      <name>G_verbose</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>u_int32</type>
      <name>G_verify</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>int32</type>
      <name>G_cycleClkNibble</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>int32</type>
      <name>G_pulseClkNibble</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>z61_doc.c</name>
    <path>/opt/menlinux/DRIVERS/MDIS_LL/Z061_PWM/DRIVER/COM/</path>
    <filename>z61__doc_8c</filename>
  </compound>
  <compound kind="file">
    <name>z61_drv.c</name>
    <path>/opt/menlinux/DRIVERS/MDIS_LL/Z061_PWM/DRIVER/COM/</path>
    <filename>z61__drv_8c</filename>
    <member kind="function">
      <type>void</type>
      <name>Z61_GetEntry</name>
      <anchor>a1</anchor>
      <arglist>(LL_ENTRY *drvP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Init</name>
      <anchor>a2</anchor>
      <arglist>(DESC_SPEC *descP, OSS_HANDLE *osHdl, MACCESS *ma, OSS_SEM_HANDLE *devSemHdl, OSS_IRQ_HANDLE *irqHdl, LL_HANDLE **llHdlP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Exit</name>
      <anchor>a3</anchor>
      <arglist>(LL_HANDLE **llHdlP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Read</name>
      <anchor>a4</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, int32 *valueP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Write</name>
      <anchor>a5</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, int32 value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_SetStat</name>
      <anchor>a6</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 code, int32 ch, INT32_OR_64 value32_or_64)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_GetStat</name>
      <anchor>a7</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 code, int32 ch, INT32_OR_64 *value32_or_64P)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_BlockRead</name>
      <anchor>a8</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, void *buf, int32 size, int32 *nbrRdBytesP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_BlockWrite</name>
      <anchor>a9</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, void *buf, int32 size, int32 *nbrWrBytesP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Irq</name>
      <anchor>a10</anchor>
      <arglist>(LL_HANDLE *llHdl)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Info</name>
      <anchor>a11</anchor>
      <arglist>(int32 infoType,...)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>char *</type>
      <name>Ident</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Cleanup</name>
      <anchor>a13</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 retCode)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char</type>
      <name>IdentString</name>
      <anchor>a0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>z61_drv.h</name>
    <path>/opt/menlinux/INCLUDE/COM/MEN/</path>
    <filename>z61__drv_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>Z061_PERIOD</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Z061_PULSE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>INT32_OR_64</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>U_INT32_OR_64</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>INT32_OR_64</type>
      <name>MDIS_PATH</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>z61_int.h</name>
    <path>/opt/menlinux/DRIVERS/MDIS_LL/Z061_PWM/DRIVER/COM/</path>
    <filename>z61__int_8h</filename>
    <class kind="struct">LL_HANDLE</class>
    <member kind="define">
      <type>#define</type>
      <name>Z061_PERIOD_ADDR_OFFSET</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Z061_PULSE_ADDR_OFFSET</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Z061_CHANNEL_OFFSET</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_NO_LL_HANDLE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CH_NUMBER</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>USE_IRQ</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ADDRSPACE_COUNT</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ADDRSPACE_SIZE</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DBG_MYLEVEL</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DBH</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Init</name>
      <anchor>a10</anchor>
      <arglist>(DESC_SPEC *descSpec, OSS_HANDLE *osHdl, MACCESS *ma, OSS_SEM_HANDLE *devSemHdl, OSS_IRQ_HANDLE *irqHdl, LL_HANDLE **llHdlP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Exit</name>
      <anchor>a11</anchor>
      <arglist>(LL_HANDLE **llHdlP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Read</name>
      <anchor>a12</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, int32 *value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Write</name>
      <anchor>a13</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, int32 value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_SetStat</name>
      <anchor>a14</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 code, int32 ch, INT32_OR_64 value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_GetStat</name>
      <anchor>a15</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 code, int32 ch, INT32_OR_64 *valueP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_BlockRead</name>
      <anchor>a16</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, void *buf, int32 size, int32 *nbrRdBytesP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_BlockWrite</name>
      <anchor>a17</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 ch, void *buf, int32 size, int32 *nbrWrBytesP)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Irq</name>
      <anchor>a18</anchor>
      <arglist>(LL_HANDLE *llHdl)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Z61_Info</name>
      <anchor>a19</anchor>
      <arglist>(int32 infoType,...)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>char *</type>
      <name>Ident</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>int32</type>
      <name>Cleanup</name>
      <anchor>a21</anchor>
      <arglist>(LL_HANDLE *llHdl, int32 retCode)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>z61_simp.c</name>
    <path>/opt/menlinux/DRIVERS/MDIS_LL/Z061_PWM/EXAMPLE/Z61_SIMP/COM/</path>
    <filename>z61__simp_8c</filename>
    <member kind="define">
      <type>#define</type>
      <name>Z61_FREQ_START</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Z61_FREQ_END</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPGA_CLK_HZ</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>PrintError</name>
      <anchor>a3</anchor>
      <arglist>(char *info)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>CalcPrintPeriodDuty</name>
      <anchor>a4</anchor>
      <arglist>(u_int16 period, u_int16 duty)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>LL_HANDLE</name>
    <filename>structLL__HANDLE.html</filename>
    <member kind="variable">
      <type>int32</type>
      <name>memAlloc</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>OSS_HANDLE *</type>
      <name>osHdl</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>OSS_IRQ_HANDLE *</type>
      <name>irqHdl</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DESC_HANDLE *</type>
      <name>descHdl</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MACCESS</type>
      <name>ma</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MDIS_IDENT_FUNCT_TBL</type>
      <name>idFuncTbl</name>
      <anchor>m5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>u_int32</type>
      <name>dbgLevel</name>
      <anchor>m6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DBG_HANDLE *</type>
      <name>dbgHdl</name>
      <anchor>m7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>u_int32</type>
      <name>irqCount</name>
      <anchor>m8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>z61dummy</name>
    <title>MEN logo</title>
    <filename>z61dummy</filename>
  </compound>
</tagfile>
