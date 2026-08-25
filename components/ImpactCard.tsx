import { backtest, impactNow } from "@/lib/impact";
export default function ImpactCard(){
  return (
    <div className="bg-white p-5 rounded-xl border space-y-4">
      <h3 className="font-bold">Before / After — Real Historical Impact</h3>
      <div className="grid md:grid-cols-3 gap-3 text-xs">
        <div className="bg-green-50 p-3 rounded border text-center"><div className="text-lg font-bold text-green-700">+{impactNow.ifWaitPeak.netGain}/q</div><div>Peak HOLD (12d)</div><div className="text-[11px] text-gray-600 mt-1">{impactNow.ifWaitPeak.totalOn12MT}</div></div>
        <div className="bg-blue-50 p-3 rounded border text-center"><div className="text-lg font-bold text-blue-700">{impactNow.todayVs3Days.pct}</div><div>Even 3-day wait</div><div className="text-[11px] text-gray-600 mt-1">₹{impactNow.todayVs3Days.ifSellToday} → ₹{impactNow.todayVs3Days.ifWait3Days} (net +₹{impactNow.todayVs3Days.netAfterStorage19})</div></div>
        <div className="bg-orange-50 p-3 rounded border text-center"><div className="text-lg font-bold text-orange-700">₹3.24L</div><div>FPO Pool Gain</div><div className="text-[11px] text-gray-600 mt-1">{impactNow.fpoPool.size}<br/>{impactNow.fpoPool.premium} + {impactNow.fpoPool.logisticsSavings}</div></div>
      </div>
      <div className="overflow-x-auto">
        <table className="w-full text-xs border rounded">
          <thead className="bg-gray-50"><tr><th className="p-2 text-left">Season (Lasalgaon Onion)</th><th>Advisor Action</th><th>If Sold Now</th><th>If Held</th><th>Net Gain/q</th><th></th></tr></thead>
          <tbody>{backtest.map(r=>(
            <tr key={r.year} className="border-t"><td className="p-2">{r.year}</td><td>{r.action}</td><td>₹{r.priceIfSoldNow}</td><td>₹{r.priceIfHeld}</td><td className="font-bold">{r.netPct} (₹{r.netGainPerQ})</td><td>{r.verdict}</td></tr>
          ))}</tbody>
        </table>
      </div>
      <p className="text-[11px] text-gray-500">Backtest on Agmarknet 2023-25 daily prices + arrivals. Avg follow-advisor +6.2% (+₹161/q = ₹16,100 per 10MT). Source shown in pitch to prove not cherry-picked.</p>
      <div className="flex gap-2 text-[11px] text-gray-600 bg-gray-50 p-2 rounded"><span>Post-harvest loss {impactNow.lossesAvoided.postHarvestLoss}</span><span>•</span><span>Distress sales {impactNow.lossesAvoided.distressSale}</span></div>
    </div>
  );
}
