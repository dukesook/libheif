const char* ism_xml = " \
<?xml-model href=\"../../Schematron/ISM/ISM_XML.sch\" type=\"application/xml\" schematypens=\"http://purl.oclc.org/dsdl/schematron\"?><!-- Distro Statement: Distribution Notice: \
 This document is being made available by the Intelligence Community Chief Information Officer \
 to Federal, State, Local, Tribal, and Foreign Partners and associated contractors. Approval for \
 any further distribution must be coordinated via the Intelligence Community Chief Information \
 Officer, at ic-standards-support@odni.gov.--><!-- All classification marks in this example are \
 for illustrative purposes only, there are no \
 actual classified data contained in this example --><test:root xmlns:test=\"test:ism\" \
 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" \
 xsi:schemaLocation=\"test:ism test_ism.xsd\"> \
 <arh:Security xmlns:arh=\"urn:us:gov:ic:arh\" \
 ism:compliesWith=\"USA-CUI USGov\" \
 ism:DESVersion=\"202111.202211\" \
 ism:ISMCATCESVersion=\"202211\" \
 ism:resourceElement=\"true\" \
 ism:createDate=\"2006-05-04\" \
 ism:classification=\"U\" \
 ism:cuiBasic=\"CMPRS JURY\" \
 ism:cuiControlledBy=\"Chief of Something\" \
 ism:cuiDecontrolEvent=\"some event\" \
 ism:disseminationControls=\"DL_ONLY\" \
 ism:ownerProducer=\"USA\"> \
 <ntk:Access xmlns:ntk=\"urn:us:gov:ic:ntk\" \
 ntk:externalReference=\"true\" \
 ism:classification=\"U\" \
 ism:ownerProducer=\"USA\"> \
 <ntk:RequiresAnyOf> \
 <ntk:AccessProfileList> \
 <ntk:AccessProfile ism:classification=\"U\" ism:ownerProducer=\"USA\"> \
 <ntk:AccessPolicy>urn:us:gov:ic:aces:ntk:permissive</ntk:AccessPolicy> \
 <ntk:ProfileDes>urn:us:gov:ic:ntk:profile:grp-ind</ntk:ProfileDes> \
 <ntk:VocabularyType ntk:name=\"individual:unclasssourceforge\" \
 ntk:source=\"UnclassSourceForge\"/> \
 <ntk:AccessProfileValue ntk:vocabulary=\"individual:unclasssourceforge\">bobstuart</ntk:AccessProfileValue> \
 <ntk:AccessProfileValue ntk:vocabulary=\"individual:unclasssourceforge\">ssun</ntk:AccessProfileValue> \
 <ntk:AccessProfileValue ntk:vocabulary=\"individual:unclasssourceforge\">cjhodges</ntk:AccessProfileValue> \
 <ntk:AccessProfileValue ntk:vocabulary=\"individual:unclasssourceforge\">cgilsenan</ntk:AccessProfileValue> \
 </ntk:AccessProfile> \
 </ntk:AccessProfileList> \
 </ntk:RequiresAnyOf> \
 </ntk:Access> \
 <ism:NoticeList ism:classification=\"U\" ism:ownerProducer=\"USA\"> \
 <ism:Notice ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
 ism:unregisteredNoticeType=\"Holiday\" \
ism:externalNotice=\"true\"> \
 <ism:NoticeText ism:classification=\"U\" ism:ownerProducer=\"USA\">Memorial day is on May 28th 2012</ism:NoticeText> \
 </ism:Notice> \
 <ism:Notice ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:unregisteredNoticeType=\"Holiday\" \
ism:externalNotice=\"true\"> \
 <ism:NoticeText ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:cuiBasic=\"CMPRS JURY\">The next Holiday will be July 4th 2012</ism:NoticeText> \
 </ism:Notice> \
 </ism:NoticeList> \
 </arh:Security> \
<test:parentElement ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:cuiBasic=\"CMPRS JURY\" \
ism:disseminationControls=\"DL_ONLY\">Executive Summary: From 1754 to 1763 Europe and the Americas were caught up in a \
 conflict between England, under King George II, and France, under King Louis XV. In Europe this period was known as \
 the Seven Years' War; in North America it came to be called the French and Indian War. It was a conflict over trade \
 and land. \
 <test:childElement ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:cuiBasic=\"CMPRS\" \
 ism:disseminationControls=\"DL_ONLY\"> \
 <test:grandchildElement ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:disseminationControls=\"DL_ONLY\">Paragraph: The English sent Crown forces from England to fortify the \
 colonies and fight the French and Indian invaders, but it was also necessary to recruit soldiers from the \
 colonial population. The English army found that fighting an enemy in the near-wilderness of North America was \
 too much for their massed regiments. The dense forests and mountainous terrain required fighting men who knew \
 the habits of the enemy and could serve effectively as scouts and skirmishers.</test:grandchildElement> \
 <test:grandchildElement ism:classification=\"U\" ism:ownerProducer=\"USA\" ism:cuiBasic=\"CMPRS\">Paragraph: Men from local communities and nearby states were recruited to \
join ranger \
 companies in the Hudson Valley campaign. The New Hampshireman Robert Rogers formed the most notable of these \
 ranger companies.</test:grandchildElement> \
 </test:childElement> \
 <test:childElement ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:cuiBasic=\"JURY\" \
 ism:disseminationControls=\"DL_ONLY\">Paragraph: Rogers grew up in southern New Hampshire, in an area which had known \
 years of murderous Indian raids. He had the knowledge and the spirit to make a good ranger commander, and both he and \
 his brother James joined the war in the King's service as rangers. Soon his own company, Rogers' Rangers, was in \
 service in the upper Hudson River area where they became known for their successful but unorthodox \
 tactics.</test:childElement> \
 </test:parentElement> \
 <test:parentElement ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:cuiBasic=\"JURY\" \
ism:disseminationControls=\"DL_ONLY\"> \
 <test:childElement ism:classification=\"U\" ism:ownerProducer=\"USA\" ism:cuiBasic=\"JURY\">Paragraph: The Rangers wore distinctive green outfits and practiced tactics called \
\"Rogers' \
 Rules of Ranging,\" which the British considered unconventional. Rogers hired men solely on merit and shocked regular \
 commanders with his use of Indians and freed slaves.</test:childElement> \
 <test:childElement ism:classification=\"U\" \
 ism:ownerProducer=\"USA\" \
ism:cuiBasic=\"JURY\" \
 ism:disseminationControls=\"DL_ONLY\"> \
 <test:grandchildElement ism:classification=\"U\" ism:ownerProducer=\"USA\" ism:cuiBasic=\"JURY\">All Rangers are to be subject to the rules and articles of war; to appear at \
roll- call \
every evening, on their own parade, equipped, each with a Firelock, sixty rounds of powder and ball, and a \
 hatchet, at which time an officer from each company is to inspect the same, to see they are in order, so as \
 to be ready on any emergency to march at a minute's warning; and before they are dismissed, the necessary \
 guards are to be draughted, and scouts for the next day appointed</test:grandchildElement> \
 <test:grandchildElement ism:classification=\"U\" ism:ownerProducer=\"USA\" ism:cuiBasic=\"JURY\">Whenever you are ordered out to the enemies forts or frontiers for \
discoveries, if your \
 number be small, march in a single file, keeping at such a distance from each other as to prevent one shot \
 from killing two men, sending one man, or more, forward, and the like on each side, at the distance of twenty \
 yards from the main body, if the ground you march over will admit of it, to give the signal to the officer of \
 the approach of an enemy, and of their number, &amp;c.</test:grandchildElement> \
 </test:childElement> \
 </test:parentElement> \
 </test:root> \
  ";

  /*
  <?xml-model href="../../Schematron/ISM/ISM_XML.sch" type="application/xml" schematypens="http://purl.oclc.org/dsdl/schematron"?><!-- Distro Statement: Distribution Notice:
 This document is being made available by the Intelligence Community Chief Information Officer
 to Federal, State, Local, Tribal, and Foreign Partners and associated contractors. Approval for
 any further distribution must be coordinated via the Intelligence Community Chief Information
 Officer, at ic-standards-support@odni.gov.--><!-- All classification marks in this example are
 for illustrative purposes only, there are no
 actual classified data contained in this example -->
<test:root xmlns:test="test:ism"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="test:ism test_ism.xsd">
    <arh:Security xmlns:arh="urn:us:gov:ic:arh"
        ism:compliesWith="USA-CUI USGov"
        ism:DESVersion="202111.202211"
        ism:ISMCATCESVersion="202211"
        ism:resourceElement="true"
        ism:createDate="2006-05-04"
        ism:classification="U"
        ism:cuiBasic="CMPRS JURY"
        ism:cuiControlledBy="Chief of Something"
        ism:cuiDecontrolEvent="some event"
        ism:disseminationControls="DL_ONLY"
        ism:ownerProducer="USA">
        <ntk:Access xmlns:ntk="urn:us:gov:ic:ntk"
            ntk:externalReference="true"
            ism:classification="U"
            ism:ownerProducer="USA">
            <ntk:RequiresAnyOf>
                <ntk:AccessProfileList>
                    <ntk:AccessProfile ism:classification="U" ism:ownerProducer="USA">
                        <ntk:AccessPolicy>urn:us:gov:ic:aces:ntk:permissive</ntk:AccessPolicy>
                        <ntk:ProfileDes>urn:us:gov:ic:ntk:profile:grp-ind</ntk:ProfileDes>
                        <ntk:VocabularyType ntk:name="individual:unclasssourceforge"
                            ntk:source="UnclassSourceForge" />
                        <ntk:AccessProfileValue ntk:vocabulary="individual:unclasssourceforge">
                            bobstuart</ntk:AccessProfileValue>
                        <ntk:AccessProfileValue ntk:vocabulary="individual:unclasssourceforge">ssun</ntk:AccessProfileValue>
                        <ntk:AccessProfileValue ntk:vocabulary="individual:unclasssourceforge">
                            cjhodges</ntk:AccessProfileValue>
                        <ntk:AccessProfileValue ntk:vocabulary="individual:unclasssourceforge">
                            cgilsenan</ntk:AccessProfileValue>
                    </ntk:AccessProfile>
                </ntk:AccessProfileList>
            </ntk:RequiresAnyOf>
        </ntk:Access>
        <ism:NoticeList ism:classification="U" ism:ownerProducer="USA">
            <ism:Notice ism:classification="U"
                ism:ownerProducer="USA"
                ism:unregisteredNoticeType="Holiday"
                ism:externalNotice="true">
                <ism:NoticeText ism:classification="U" ism:ownerProducer="USA">Memorial day is on
                    May 28th 2012</ism:NoticeText>
            </ism:Notice>
            <ism:Notice ism:classification="U"
                ism:ownerProducer="USA"
                ism:unregisteredNoticeType="Holiday"
                ism:externalNotice="true">
                <ism:NoticeText ism:classification="U"
                    ism:ownerProducer="USA"
                    ism:cuiBasic="CMPRS JURY">The next Holiday will be July 4th 2012</ism:NoticeText>
            </ism:Notice>
        </ism:NoticeList>
    </arh:Security>
    <test:parentElement ism:classification="U"
        ism:ownerProducer="USA"
        ism:cuiBasic="CMPRS JURY"
        ism:disseminationControls="DL_ONLY">Executive Summary: From 1754 to 1763 Europe and the
        Americas were caught up in a conflict between England, under King George II, and France,
        under King Louis XV. In Europe this period was known as the Seven Years' War; in North
        America it came to be called the French and Indian War. It was a conflict over trade and
        land. <test:childElement ism:classification="U"
            ism:ownerProducer="USA"
            ism:cuiBasic="CMPRS"
            ism:disseminationControls="DL_ONLY">
            <test:grandchildElement ism:classification="U"
                ism:ownerProducer="USA"
                ism:disseminationControls="DL_ONLY">Paragraph: The English sent Crown forces from
        England to fortify the
                colonies and fight the French and Indian invaders, but it was also necessary to
        recruit soldiers from the
                colonial population. The English army found that fighting an enemy in the
        near-wilderness of North America was
                too much for their massed regiments. The dense forests and mountainous terrain
        required fighting men who knew
                the habits of the enemy and could serve effectively as scouts and skirmishers.</test:grandchildElement>
            <test:grandchildElement ism:classification="U" ism:ownerProducer="USA"
                ism:cuiBasic="CMPRS">Paragraph: Men from local communities and nearby states were
        recruited to
                join ranger
                companies in the Hudson Valley campaign. The New Hampshireman Robert Rogers formed
        the most notable of these
                ranger companies.</test:grandchildElement>
        </test:childElement>
 <test:childElement
            ism:classification="U"
            ism:ownerProducer="USA"
            ism:cuiBasic="JURY"
            ism:disseminationControls="DL_ONLY">Paragraph: Rogers grew up in southern New Hampshire,
        in an area which had known
            years of murderous Indian raids. He had the knowledge and the spirit to make a good
        ranger commander, and both he and
            his brother James joined the war in the King's service as rangers. Soon his own company,
        Rogers' Rangers, was in
            service in the upper Hudson River area where they became known for their successful but
        unorthodox
            tactics.</test:childElement>
    </test:parentElement>
    <test:parentElement ism:classification="U"
        ism:ownerProducer="USA"
        ism:cuiBasic="JURY"
        ism:disseminationControls="DL_ONLY">
        <test:childElement ism:classification="U" ism:ownerProducer="USA" ism:cuiBasic="JURY">Paragraph:
            The Rangers wore distinctive green outfits and practiced tactics called
            "Rogers'
            Rules of Ranging," which the British considered unconventional. Rogers hired men solely
            on merit and shocked regular
            commanders with his use of Indians and freed slaves.</test:childElement>
        <test:childElement ism:classification="U"
            ism:ownerProducer="USA"
            ism:cuiBasic="JURY"
            ism:disseminationControls="DL_ONLY">
            <test:grandchildElement ism:classification="U" ism:ownerProducer="USA"
                ism:cuiBasic="JURY">All Rangers are to be subject to the rules and articles of war;
                to appear at
                every evening, on their own parade, equipped, each with a Firelock, sixty rounds of
                powder and ball, and a
                hatchet, at which time an officer from each company is to inspect the same, to see
                they are in order, so as
                to be ready on any emergency to march at a minute's warning; and before they are
                dismissed, the necessary
                guards are to be draughted, and scouts for the next day appointed</test:grandchildElement>
            <test:grandchildElement ism:classification="U" ism:ownerProducer="USA"
                ism:cuiBasic="JURY">Whenever you are ordered out to the enemies forts or frontiers
                for
                discoveries, if your
                number be small, march in a single file, keeping at such a distance from each other
                as to prevent one shot
                from killing two men, sending one man, or more, forward, and the like on each side,
                at the distance of twenty
                yards from the main body, if the ground you march over will admit of it, to give the
                signal to the officer of
                the approach of an enemy, and of their number, &amp;c.</test:grandchildElement>
        </test:childElement>
    </test:parentElement>
</test:root>
  
  
  */