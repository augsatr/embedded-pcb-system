import PriceChart from "@/components/PriceChart";
import { mandiPrices, buyers, saleWindowAdvice } from "@/lib/mockData";
import Link from "next/link";

export default function Dashboard(){
  return (
    <div className="space-y-6">
      <div className="grid md:grid-cols-4 gap-4">
        <div className="bg-krishi-600 text-white p-4 rounded-xl"><div className="text-sm opacity-90">Avg Price Realisation</div><div className="text-2xl font-bold">₹2,850/q</div><div className="text-xs">↑ 8.2% vs last month</div></div>
        <div className="bg-white p-4 rounded-xl border"><div className="text-sm text-gray-500">Active Lots</div><div className="text-2xl font-bold">3</div><div className="text-xs text-green-600">2 matched with buyers</div></div>
        <div className="bg-white p-4 rounded-xl border"><div className="text-sm text-gray-500">Verified Buyers Nearby</div><div className="text-2xl font-bold">12</div><div className="text-xs">within 50km</div></div>
        <div className="bg-white p-4 rounded-xl border"><div className="text-sm text-gray-500">Pending Payments</div><div className="text-2xl font-bold">₹1.2L</div><div className="text-xs text-orange-600">1 delayed - grievance enabled</div></div>
      </div>

      <div className="grid lg:grid-cols-3 gap-6">
        <div className="lg:col-span-2"><PriceChart /></div>
        <div className="bg-gradient-to-br from-orange-50 to-amber-50 p-5 rounded-xl border border-orange-200">
          <h3 className="font-bold text-mandi-600 flex gap-2">🤖 Sale-Window Advisor</h3>
          <div className="mt-3 bg-white p-3 rounded-lg border">
            <div className="text-sm font-semibold">{saleWindowAdvice.commodity}: <span className="text-green-600">{saleWindowAdvice.recommendation}</span></div>
            <p className="text-xs text-gray-600 mt-2">{saleWindowAdvice.reason}</p>
            <div className="mt-2 text-xs font-medium text-green-700 bg-green-50 p-2 rounded">{saleWindowAdvice.expectedGain}</div>
            <div className="text-xs text-orange-600 mt-1">Risk: {saleWindowAdvice.risk}</div>
          </div>
          <div className="mt-3 flex gap-2">
            <Link href="/forecast" className="text-xs bg-krishi-600 text-white px-3 py-1.5 rounded">View Details</Link>
            <Link href="/logistics" className="text-xs bg-white border px-3 py-1.5 rounded">Find Storage</Link>
          </div>
          <p className="text-[10px] text-gray-500 mt-3">Localized to Junnar, Pune • Accounts for liquidity, storage cost, and transport.</p>
        </div>
      </div>

      <div className="grid md:grid-cols-2 gap-6">
        <div className="bg-white rounded-xl border">
          <div className="p-4 border-b flex justify-between"><h3 className="font-semibold">Nearby Mandi Prices (Live)</h3><Link href="/markets" className="text-xs text-krishi-600">View all →</Link></div>
          <table className="w-full text-sm">
            <thead className="bg-gray-50 text-xs text-gray-500"><tr><th className="p-2 text-left">Market</th><th className="p-2">Commodity</th><th className="p-2">Modal (₹/q)</th><th className="p-2">Trend</th></tr></thead>
            <tbody>{mandiPrices.slice(0,4).map(m=>(
              <tr key={m.market} className="border-t"><td className="p-2">{m.market}<div className="text-xs text-gray-400">{m.distanceKm}km • {m.arrivalQty}q arrival</div></td><td className="p-2 text-center">{m.commodity}</td><td className="p-2 text-center font-semibold">₹{m.modalPrice}</td><td className="p-2 text-center">{m.trend==="up"?"📈":m.trend==="down"?"📉":"➡️"}</td></tr>
            ))}</tbody>
          </table>
        </div>
        <div className="bg-white rounded-xl border">
          <div className="p-4 border-b flex justify-between"><h3 className="font-semibold">Matching Verified Buyers</h3><Link href="/buyers" className="text-xs text-krishi-600">Explore →</Link></div>
          <div className="divide-y">
            {buyers.slice(0,3).map(b=>(
              <div key={b.id} className="p-3 flex justify-between items-center">
                <div><div className="font-medium text-sm flex gap-1">{b.name} {b.verified&&<span className="text-[10px] bg-green-600 text-white px-1 rounded">✔ Verified</span>}</div><div className="text-xs text-gray-500">{b.type} • {b.commodity} • {b.qualityGrade} • {b.location}</div></div>
                <div className="text-right"><div className="font-bold text-sm">₹{b.offerPrice}/q</div><div className="text-xs text-gray-500">{b.requiredQty}q • ⭐{b.rating}</div></div>
              </div>
            ))}
          </div>
        </div>
      </div>

      <div className="bg-white p-4 rounded-xl border">
        <h3 className="font-semibold mb-2">How KrishiConnect solves PS 26132</h3>
        <div className="grid md:grid-cols-4 gap-3 text-xs">
          <div className="p-3 bg-gray-50 rounded"><b>1. Aggregate</b><br/>Mandi+eNAM+buyer demand+arrivals+weather in one place</div>
          <div className="p-3 bg-gray-50 rounded"><b>2. Advise</b><br/>Localized price forecast + hold/sell window after storage/transport cost</div>
          <div className="p-3 bg-gray-50 rounded"><b>3. Match & Transact</b><br/>Lot creation, AI grading (photo), digital offers, negotiation</div>
          <div className="p-3 bg-gray-50 rounded"><b>4. Fulfil & Trust</b><br/>Logistics, escrow payment tracking, grievance & transparent ledger</div>
        </div>
      </div>
    </div>
  );
}
