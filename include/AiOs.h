/******************************************************************************

           Copyright (c) AIM GmbH 2009, 79111 Freiburg, Germany.

            All rights reserved.  No part of this software may
            be published, distributed, translated or otherwise
            reproduced by any means or for any purpose without
            the prior written consent of AIM GmbH, Freiburg.

-------------------------------------------------------------------------------
-   $Workfile:   AiOs.h  $
-   $Revision:   1.8  $
-------------------------------------------------------------------------------

    Description: Include file for operating system specific functions and headers
-------------------------------------------------------------------------------

    History :

    $Log:   S:/AIM_PVCS/archives/PCI-SW-1553-3910/Host/Spg/AiOs.h-arc  $

   Rev 1.8   Jul 08 2014 12:33:18   Peter Baumhöfer
Merged with previous version

   Rev 1.7   Jul 07 2014 14:37:18   Peter Baumhöfer
V04.10

   Rev 1.6   Apr 24 2014 10:58:40   Martin Haag
AXI 3910 BSP V11.20 RC1

   Rev 1.5   Dec 22 2011 16:18:20   Rolf Heitzmann
changed <> to ""

   Rev 1.4   Apr 19 2011 15:18:58   Jochen Pfaadt
Removed prototypes

   Rev 1.3   Sep 27 2010 12:34:00   Jochen Pfaadt
Add VxWorks

   Rev 1.2   15 Jun 2010 10:35:04   Markus Melcher
Regard case sensitivity in include statement

   Rev 1.1   Apr 26 2010 08:49:24   Martin Haag
Corrected AiOsSleep function

   Rev 1.0   Jan 07 2010 15:46:14   Martin Haag
Initial revision.
*/


#ifndef AIOS_H
#define AIOS_H

#if defined _AIM_WINDOWS || defined _AIM_VMEWINDOWS 
  /* Windows operating systems */
  #include "aioswindows.h"
#elif defined _AIM_VXI
  /* LabViewRT operating systems */
  #include "AiOsLabViewRT.h" 
#elif defined _AIM_LINUX
  /* Linux operating systems */
  #include "AiOsLinux.h"
#elif defined __VXWORKS__
  /* VxWorks operating systems */
  #include "AiOsVxWorks.h"
#endif 


#endif /* AIOS_H */
